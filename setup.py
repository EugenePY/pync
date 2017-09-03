"""
Compile C module
"""
from numpy.distutils.misc_util import Configuration
import os


def configuration(parent_package='', top_path=None):
    """config."""
    config = Configuration('c_modules', parent_package, top_path)
    config.add_extension('gemm', [os.path.join('./src', 'gemm_simple.c')])
    return config

if __name__ == "__main__":
    from numpy.distutils.core import setup
    setup(configuration=configuration)
