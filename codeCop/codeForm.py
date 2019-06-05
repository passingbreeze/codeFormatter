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
    def __init__(self, fpath, fname, thres):
        self.fpath = fpath
        self.fname = fname
        self.t = thres

    def _overMaxflen(self, fpath, fname):
        if sys.platform.startswith('windows') and len(fpath) > 260 :
            return True
        elif (sys.platform.startswith('linux') or sys.platform.startswith('darwin')) and len(fname) > 255:
            return True
        else:
            return False

    def decerr(self):
        if self._overMaxflen(self.fpath, self.fname):
            return ('e1', "Too Long Name")
        elif getsize(self.fpath) > self.t:
            return ('e3', "Too Big File")
        elif getsize(self.fpath) == 0:
            return ('e4', "Empty Source File")
        return False
'''
    def decErr(e, fname, fpath, t):
        if overMaxflen(fpath, fname):
            e['e1'][fpath] = "Too Long Name"
            return True
        elif getsize(fpath) > t:
            e['e3'][fpath] = "Too Big File"
            return True
        elif getsize(fpath) == 0:
            e['e4'][fpath] = "Empty Source File"
            return True
        return False
'''
class codeform:
    def __init__(self, thres, rpath):
        self.thres = thres
        self.rpath = rpath
        self.plist = [join(rpath, i) for i in filter(lambda d : isdir(d), os.listdir(rpath))]
        self.cpat, self.hpat = re.compile(r".*[.].*c$"), re.compile(r".*[.].*h$")

    def _analyProj(self, a, err, dir, thres):
        # loop directories...
        ctemp, htemp = [],[]
        log = []
        for root, dirs, files in os.walk(dir):
            if len(dirs) == 0 and len(files) == 0:
                log.append("%s !! %s" % (str(datetime.datetime.now()), root))
                err['e2'][root] = "Empty Folder"
                continue
            for f in files:
                logd = str(datetime.datetime.now())
                lineCount = 0
                findC, findH = _C.search(f), _H.search(f)
                if findC is not None:
                    cfname = findC.group()
                    cfpath = join(root, cfname)
                    if decErr(err, cfname, cfpath, thres):
                        logd += "  !!  Error  !!  %s" % cfpath
                        log.append(logd)
                        continue
                    else:
                        print("cpath :", cfpath)
                        a['e0'][cfpath] = {'fsize' : "%s" % str(getsize(cfpath))}
                        with open(cfpath, "r", encoding='utf-8') as fic:
                            try :
                                ctemp = fic.readlines()
                            except UnicodeDecodeError:
                                err['ee'][cfpath] = "Unicode Decode Error"
                            if len(ctemp) != 0 :
                                for line in ctemp:
                                    lineCount+=1
                        a['pline'] += lineCount
                        a['e0'][cfpath]['flines'] = str(lineCount)
                        logd += "  %s" % cfpath
                        log.append(logd)
                elif findH is not None:
                    hfname = findH.group()
                    hfpath = join(root, hfname)
                    if decErr(err, hfname, hfpath, thres):
                        logd += "  !!  Error  !!  %s" % hfpath
                        log.append(logd)
                        continue
                    else:
                        a['e0'][hfpath] = {'fsize': "%s" % str(getsize(hfpath))}
                        with open(hfpath, "r", encoding='utf-8') as fih:
                            try:
                                htemp = fih.readlines()
                            except UnicodeDecodeError:
                                err['ee'][hfpath] = "Unicode Decode Error"
                            if len(htemp) != 0:
                                for line in htemp:
                                    lineCount += 1
                        a['pline'] += lineCount
                        a['e0'][hfpath]['flines'] = str(lineCount)
                        logd += "  !!  %s" % hfpath
                        log.append(logd)
                else:
                    err['e2'][join(root)] = "No C source files."
                    logd += "  !!  %s" % root
                    log.append(logd)
                    continue
        # print(log)
        return log

def getReslist(rlist, plist, thres):
    logs = []
    for p in plist:
        anap = {'psize': 0, 'pline': 0, 'e0': {}}
        erc = {'e1': {}, 'e2': {}, 'e3': {}, 'e4': {}, 'ee':{}}
        anap['psize'] = getsize(p)
        logs.append('\n'.join(analyProj(anap, erc, p, thres)))
        rlist.append((p, anap, erc))

    with open("flog.txt", "w", encoding='utf-8') as lf:
        lf.write('\n'.join(logs))

def getResfile(rlist):
    for p, r, e in rlist:
        with open("%s_origin.spec" % p, "w", encoding='utf-8') as stt:
            json.dump(r, stt, indent=4)
        with open("%s_origin_error.spec" % p, "w", encoding='utf-8') as stt:
            json.dump(e, stt, indent=4)

def main():
    thres = (2 ** 20) // (2 ** 3)  # 1 Mbit 보다 크면 Out!
    ROOT_PATH = '/Users/hongjeongmin/Documents/coding/codeCop/workspace'
    ex = codeform(thres, ROOT_PATH)
    projlist = getProjlist(ROOT_PATH)

    sp.call("find -L %s ! -name \"*.c\" ! -name \"*.h\" -delete" % (ROOT_PATH), shell=True)
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
