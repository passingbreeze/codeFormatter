import time
import os, sys, subprocess as sp, re, json, datetime
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
        self.cpat, self.hpat = re.compile(r".*[.].*c$"), re.compile(r".*[.].*h$")
        self.codes = { 'e1' : {},
                       'e2' : {},
                       'e3' : {},
                       'e4' : {},
                       'ee' : {}  }

    def _overMaxflen(self, fpath, fname):
        if sys.platform.startswith('windows') and len(fpath) > 260 :
            return True
        elif (sys.platform.startswith('linux') or sys.platform.startswith('darwin')) and len(fname) > 255:
            return True
        else:
            return False

    def errchk(self):
        for k, v in self.codes:
            if len(self.codes[k]) == 0:
                return False
        return True

    def ferr(self, fpath, fname):
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

    def derr(self, root, dir, files):
        cp, hp = self.cpat.search(files), self.hpat.search(files)
        if len(dir) == 0 and len(files) == 0:
            self.codes['e2'][root] = "Empty Folder"
            return True
        else :
            if cp is None and hp is None:
                self.codes['e2'][dir] = "No C source files."
                return True
            else:
                return False

    def gexerr(self, dir):
        self.codes['ee'][dir] = "Not Defined Error Occured."

    def getCode(self):
        return self.codes

class flog:
    def __init__(self):
        self.log = []

    def wlog(self, dir):
        self.log.append("%s !! %s" % (str(datetime.datetime.now()), dir))

    def wedlog(self, dir):
        self.log.append("%s !! Error !! %s" % (str(datetime.datetime.now()), dir))

    def getlog(self):
        return '\n'.join(self.log)

class projanaly:
    def __init__(self, thres, dir):
        self.thres = thres
        self.dir = dir
        self.cpat, self.hpat = re.compile(r".*[.].*c$"), re.compile(r".*[.].*h$")
        self.result = { 'pbytes': 0,
                        'porg_files_folders': 0,
                        'porg_clines': 0,
                        'pafter_bytes': 0,
                        'pafter_files_folders': 0,
                        'pafter_clines': 0,
                        'e0': {} }
        self.pecode = ecode(self.thres)
        self.log = flog()

    def _findcs(self, root, file):
        lineCount = 0
        findC, findH = self.cpat.search(file), self.hpat.search(file)
        ctemp, htemp = [],[]
        if findC is not None:
            cfname = findC.group()
            cfpath = join(root, cfname)
            if self.pecode.ferr(cfname, cfpath):
                self.log.wlog(cfpath)
            else:
                # print("cpath :", cfpath)
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

        elif findH is not None:
            hfname = findH.group()
            hfpath = join(root, hfname)
            if self.pecode.ferr(hfname, hfpath):
                self.log.wlog(hfpath)
                return 0
            else:
                self.result['e0'][hfpath] = {'fsize': "%s" % str(getsize(hfpath))}
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

    def analorg(self):
        fcount, dcount, linec = 0, 0, 0
        self.result['pbytes'] = getsize(self.dir)
        for r, d, f in os.walk(self.dir):
            if self.pecode.derr(r,d,f):
                self.log.welog(r)
                continue
            else:
                if len(d) != 0:
                    print(d)
                    dcount += len(d)
                if len(f) != 0:
                    print(f)
                    fcount += len(f)
                    linec += self._findcs(r, f)
        self.result['porg_files'] = fcount + dcount
        self.result['porg_clines'] += linec
        sp.call("find -L %s ! -name \"*.c\" ! -name \"*.h\" -delete" % (self.dir), shell=True)

    def analafter(self):
        # loop directories...
        for root, dirs, files in os.walk(self.dir):
            for f in files:
                if self._findcs(root, files) != 0:
                    self.result['pafter_clines'] += self._findcs(root, files)
                    self.log.wlog(root)
                else:
                    if self.pecode.derr(root, dirs, f):
                        self.log.welog(root)
                        continue

# def getReslist(rlist, plist, thres):
#     logs = []
#     for p in plist:
#         pe = projanaly(thres, p)
#         pe.analorg()
#         logs.append('\n'.join(analyProj(anap, erc, p, thres)))
#         rlist.append((p, anap, erc))
#
#     with open("flog.txt", "w", encoding='utf-8') as lf:
#         lf.write('\n'.join(logs))
#
# def getResfile(rlist):
#     for p, r, e in rlist:
#         with open("%s_origin.spec" % p, "w", encoding='utf-8') as stt:
#             json.dump(r, stt, indent=4)
#         with open("%s_origin_error.spec" % p, "w", encoding='utf-8') as stt:
#             json.dump(e, stt, indent=4)

def main():
    thres = (2 ** 20) // (2 ** 3)  # 1 Mbit 보다 크면 Out!
    ROOT_PATH = './workspace'
    plist = [join(ROOT_PATH, i) for i in filter(lambda d: isdir(d), os.listdir(ROOT_PATH))]
    for p in plist:
        ex = projanaly(thres, ROOT_PATH)

    # sp.call("find -L %s ! -name \"*.c\" ! -name \"*.h\" -delete" % (ROOT_PATH), shell=True)
    # find . ! -name "*.c" ! -name "*.h" -delete -> *.c *.h 제외하고 삭제

    resList = []
    getReslist(resList, projlist, thres)
    getResfile(resList)
    # sp.call("astyle --style=google %s/*.c, *.h" , shell=True)

if __name__ == '__main__':
    beg = time.time()
    main()
    print("--- %.6f sec(s) ---" % (time.time() - beg))

    # def getProjlist(rpath):
    #     return [join(rpath,i) for i in filter(lambda d : isdir(d), os.listdir(rpath))]
