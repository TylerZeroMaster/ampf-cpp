project('concurrent_queue_ex', 'cpp')

gmp_version = '>= 6.2.1'

deps = [
	dependency('threads'),
	dependency('gmp', version: gmp_version),
	dependency('gmpxx', version: gmp_version),
]

include_dirs = include_directories('.')
subdir('src')