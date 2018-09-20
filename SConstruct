#!/bin/python3

env = Environment()

sources = []

def add_sources(self, sources, filetype):
    import glob
    dir = self.Dir('.').abspath
    list = glob.glob(dir + "/" + filetype)
    for f in list:
        sources.append(self.Object(f))

env.sources = sources
env.__class__.add_sources = add_sources

env.Append(CXXFLAGS=['-std=c++14'])
env.Append(CPPPATH=['#'])

Export('env')

SConscript('#stbi/SCsub')
SConscript('#glad/SCsub')
SConscript('#shader/SCsub')
SConscript('#model/SCsub')
SConscript('#texture/SCsub')

env.Append(LIBS=['glfw'])

env.add_sources(env.sources, 'glad.c')
env.add_sources(env.sources, 'main.cpp')

env.Program('#bin/app',env.sources)
