import time
import os, sys, subprocess as sp, json, datetime
from os.path import *
from functools import *

'''
set ErrorCode

 0 : No Error
 1 : Over 255 chars of filename
 
[ Project ]
 2 : Empty Folder
 
[ Sources ] 
 3 : Too much big file
 4 : Empty Source file
 
 https://docs.microsoft.com/ko-kr/windows/desktop/FileIO/naming-a-file -> 윈도우 파일명 길이제한
 
'''

class ecode:
    def __init__(self, thres):
        self.t = thres
        self.codes = { 'e1' : {},
                       'e2' : {},
                       'e3' : {},
                       'e4' : {},
                       'ee' : {}  }

    def _overMaxflen(self, fpath, fname): # check file name length
        if sys.platform.startswith('windows') and len(fpath) > 260 :
            return True
        elif (sys.platform.startswith('linux') or sys.platform.startswith('darwin')) and len(fname) > 255:
            return True
        else:
            return False

    def errchk(self): # check error detected files or folders in codes
        for k, v in self.codes:
            if len(self.codes[k]) == 0:
                return False
        return True

    def ferr(self, fpath, fname): # check file errorcode
        # print(fpath, fname)
        if self._overMaxflen(fpath, fname):
            self.codes['e1'][fpath] = "Too Long Name"
            return True
        elif getsize(fpath) > self.t:
            self.codes['e3'][fpath] = "Too Big File"
            return True
        elif getsize(fpath) == 0:
            self.codes['e4'][fpath] = "Empty Source File"
            return True
        return False

    def derr(self, root, dir, files): # check folder errorcode
        # print(files)
        if len(dir) == 0 and len(files) == 0:
            self.codes['e2'][root] = "Empty Folder"
            return True
        else :
            for file in files:
                if not file.endswith(".c") and not file.endswith(".h"):
                    self.codes['e2'][file] = "No C source files."
                    return True
                else:
                    return False

    def gexerr(self, dir): # check error except errorcode
        self.codes['ee'][dir] = "Not Defined Error Occured."

    def getCode(self): # get total error statistics
        return self.codes

class flog: # write log
    def __init__(self):
        self.log = []

    def wlog(self, dir):
        self.log.append("%s !! %s" % (str(datetime.datetime.now()), dir))

    def wedlog(self, dir):
        self.log.append("%s !! Error !! %s" % (str(datetime.datetime.now()), dir))

    def getlog(self):
        return '\n'.join(self.log)

class projanaly: # analyse project
    def __init__(self, thres, dir):
        self.thres = thres
        self.dir = dir
        self.result = { 'porg_bytes': 0,
                        'porg_files': 0,
                        'porg_clines': 0,
                        'pafter_bytes': 0,
                        'pafter_files': 0,
                        'pafter_clines': 0,
                        'e0': {} }
        self.pecode = ecode(self.thres)
        self.log = flog()

    def _execAstyle(self): # execute formatter installed in OS
        if sys.platform.startswith('windows') :
            fpath = self.dir.split('\\')[-1]
        else :
            fpath = self.dir.split('/')[-1]
        new_dir =  self.dir.replace(fpath, "Formatted_"+fpath) if "Formatted_" not in fpath else self.dir
        if new_dir != self.dir:
            sp.call("/usr/bin/find -L %s ! -name \"*.c\" ! -name \"*.h\" -delete" % (self.dir), shell=True)
            sp.call("/usr/bin/mkdir %s" % new_dir, shell=True)
            sp.call("/usr/bin/cp -r %s %s" % (self.dir, new_dir), shell=True)
            os.chmod(new_dir, 0o777)
            sp.call("/usr/bin/rm -rf %s" % self.dir, shell=True)
            self.dir = new_dir
            sp.call("/usr/local/bin/astyle --style=google --indent=spaces=2 --max-code-length=80\
             --pad-header --unpad-paren --keep-one-line-blocks --mode=c %s/*.c, *.h" % new_dir , shell=True)

    def _findcs(self, root, file): # find c source files including headers
        lineCount = 0
        ctemp, htemp = [],[]
        if file.endswith(".c"):
            cfpath = join(root, file)
            if self.pecode.ferr(cfpath, file):
                self.log.wedlog(cfpath)
                return 0
            else:
                self.result['e0'][cfpath] = {'fbytes': "%s" % str(getsize(cfpath))}
                with open(cfpath, "r", encoding='utf-8') as fic:
                    try:
                        ctemp = fic.readlines()
                    except UnicodeDecodeError:
                        self.pecode.gexerr(cfpath)
                    if len(ctemp) != 0:
                        for line in ctemp:
                            lineCount += 1
                self.result['e0'][cfpath]['flines'] = str(lineCount)
                self.log.wlog(cfpath)

        elif file.endswith(".h"):
            hfpath = join(root, file)
            if self.pecode.ferr(hfpath, file):
                self.log.wedlog(hfpath)
                return 0
            else:
                self.result['e0'][hfpath] = {'fbytes': "%s" % str(getsize(hfpath))}
                with open(hfpath, "r", encoding='utf-8') as fih:
                    try:
                        htemp = fih.readlines()
                    except UnicodeDecodeError:
                        self.pecode.gexerr(hfpath)
                    if len(htemp) != 0:
                        for line in htemp:
                            lineCount += 1
                self.result['e0'][hfpath]['flines'] = str(lineCount)
                self.log.wlog(hfpath)

        return lineCount

    def analorg(self): # analyse original project
        fcount, linec = 0, 0
        for r, d, f in os.walk(self.dir):
            if self.pecode.derr(r,d,f):
                self.log.wedlog(r)
            if len(f) != 0:
                fcount += len(f)
                for t in f:
                    self.result['porg_bytes'] += getsize(join(r,t))
                    linec += self._findcs(r, t)
        self.result['porg_files'] = str(fcount)
        self.result['porg_clines'] += linec
        self._execAstyle()

    def analafter(self): # analyse formatted project
        fcount, linec = 0, 0
        for r, d, f in os.walk(self.dir):
            fcount += len(f)
            for t in f:
                self.result['pafter_bytes'] += getsize(join(r,t))
                linec += self._findcs(r, t)
        self.result['pafter_files'] = str(fcount)
        self.result['pafter_clines'] += linec

    def getResult(self):
        for k,v in self.result.items():
            if isinstance(self.result[k], int):
                self.result[k] = str(self.result[k])
        self.result.update(self.pecode.getCode())
        return (self.result, self.log.getlog())

def main(argv):
    thres = (2 ** 20) // (2 ** 3)  # if file size is bigger than 1 Mbit, Out!.(example val)
    ROOT_PATH = argv[1] # argv[1] == workspace path

    # get project folders in workspace
    plist = [join(ROOT_PATH, i) for i in os.listdir(ROOT_PATH)]
    llist = []
    for p in plist: # analyse projects, formatting and get result of analysis
        if not isdir(p):
            continue
        ex = projanaly(thres, p)
        ex.analorg()
        ex.analafter()
        fin = ex.getResult()
        with open("%s.spec" % p, "w", encoding='utf-8') as fout:
            json.dump(fin[0], fout, indent=4)
        os.chmod("%s.spec" % p,0o777)
        llist.append(fin[1])

    # write log file
    today = (datetime.datetime.today().date().isoformat()).replace("-","")
    with open("%s.flog" % today, "w", encoding='utf-8') as tout:
        tout.write('\n'.join(llist))

if __name__ == '__main__':
    beg = time.time()
    main(sys.argv)
    print("--- %.6f sec(s) ---" % (time.time() - beg))
