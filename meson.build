project('ampf-cpp', 'cpp',
	version: '1.0.4-beta',
	license: 'GNU GPLv3',
	meson_version: '>= 0.53.0'
)

gmp_version = '>= 6.2.1'

deps = [
	dependency('threads'),
	dependency('gmp', version: gmp_version),
	dependency('gmpxx', version: gmp_version),
]

conf = configuration_data()

conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('PACKAGE', 'ampf-cpp')
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('PACKAGE_STRING', 'ampf-cpp ' + meson.project_version())
conf.set_quoted('GETTEXT_PACKAGE', 'ampf-cpp')

configure_file(output: 'config.h', configuration: conf)

include_dirs = include_directories('.')
subdir('src')