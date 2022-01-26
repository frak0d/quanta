project('quanta', 'cpp', subproject_dir: 'libs',
		default_options: ['buildtype=release', 'strip=true'])

deps = [
	dependency('threads'),
	dependency('fftw3f'),
]

executable('quanta', 'src/main.cpp', dependencies: deps, override_options: ['cpp_std=c++20'])
