from distutils.core import setup, Extension

module1 = Extension('summodule',
                    sources=['sum.c'])

setup(name='SumModule',
      version='1.0',
      description='This is a demo C extension module',
      ext_modules=[module1])
