project('concurrent_queue_ex', 'cpp',
	version: '1.0.4-beta',
	license: 'MIT',
	meson_version: '>= 0.43.0'
)

gmp_version = '>= 6.2.1'

deps = [
	dependency('threads'),
	dependency('gmp', version: gmp_version),
	dependency('gmpxx', version: gmp_version),
]

conf = configuration_data()

conf.set_quoted('VERSION', meson.project_version())
conf.set_quoted('PACKAGE', 'concurrent_queue_ex')
conf.set_quoted('PACKAGE_VERSION', meson.project_version())
conf.set_quoted('PACKAGE_STRING', 'concurrent_queue_ex ' + meson.project_version())
conf.set_quoted('GETTEXT_PACKAGE', 'concurrent_queue_ex')

configure_file(output: 'config.h', configuration: conf)

include_dirs = include_directories('.')
subdir('src')