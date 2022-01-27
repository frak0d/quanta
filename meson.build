project('quanta', 'cpp', subproject_dir: 'libs',
        default_options: ['buildtype=release', 'strip=true',
                          'b_lto=true', 'b_lto_mode=thin',
                          'warning_level=3', 'cpp_std=c++20'])

deps = [
    dependency('threads'),
    dependency('fftw3f', version: '>=3.3'),
]

dir_base = meson.current_source_dir()
dir_install = join_paths(dir_base, 'build')
dir_install_assets = join_paths(dir_install, 'assets')

install_subdir('assets', strip_directory: true,
               install_dir: dir_install_assets)

executable('quanta', 'src/main.cpp',
           dependencies: deps,
           install: true,
           install_dir: dir_install,
           override_options: ['cpp_rtti=false'])
