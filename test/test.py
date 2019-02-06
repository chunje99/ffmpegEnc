#-*- coding: utf-8 -*-
from ctypes import *
lib = cdll.LoadLibrary('../lib/libpythonfenc.so')

class Fenc(object):
    def __init__(self):
        self.lib = lib
        lib.Fenc_new.restype = c_void_p
        self.obj = c_void_p(lib.Fenc_new())
    def __del__(self):
        print('__del__')
        lib.Fenc_delete.argtypes = [c_void_p]
        lib.Fenc_delete(self.obj)

    def setSource(self, src):
        lib.Fenc_setSource.argtypes = [c_void_p,c_char_p]
        lib.Fenc_setSource(self.obj, src)

    def getSource(self):
        lib.Fenc_getSource.restype = c_wchar_p
        return lib.Fenc_getSource(self.obj)

    def setTarget(self, target):
        lib.Fenc_setTarget(self.obj, target)

    def getTarget(self):
        lib.Fenc_getTarget.restype = c_char_p
        return lib.Fenc_getTarget(self.obj)

    def setPreset(self, preset):
        lib.Fenc_setPreset(self.obj, preset)

    def getPreset(self):
        lib.Fenc_getPreset.restype = c_char_p
        return lib.Fenc_getPreset(self.obj)

    def setThumbnailTime(self, ttime):
        lib.Fenc_setThumbnailTime(self.obj, ttime)

    def getThumbnailTime(self):
        return lib.Fenc_getThumbnailTime(self.obj)

    def getProgress(self):
        return lib.Fenc_getProgress(self.obj)

    def StartEncode(self):
        lib.Fenc_StartEncode(self.obj)

    def StartThumbnail(self):
        lib.Fenc_StartThumbnail(self.obj)

f = Fenc()
f.setSource("/home/ho80/다운로드/a_h_e152.mp4")
f.setTarget("out.mp4")
f.setPreset("SD")
print(f.getSource())
print(f.getTarget())
print(f.getPreset())
#f.StartEncode()
f.setTarget("out.jpg")
f.setThumbnailTime(2)
print(f.getThumbnailTime())
f.StartThumbnail()
del f
