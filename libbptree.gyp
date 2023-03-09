{
	'variables': {
		'os%': 'linux',
	},
	'targets': [
		{
			'target_name': 'libbptree',
			'type': 'static_library',
			'include_dirs': [ 'include', ],
			'direct_dependent_settings': {
				'include_dirs': [ 'include', ],
			},
			'cflags': [ '-std=c99', '-pedantic', '-pthread', '-O3' ],
			'ldflags': [ '-pthread' ],
			'defines': [
				'_LARGEFILE_SOURCE',
				'_FILE_OFFSET_BITS=64',
				'_XOPEN_SOURCE=500',
				'_DARWIN_C_SOURCE',
			],
			'sources': [
				'include/bptree.h',
				'bptree.c',
				'compressor.h',
				'pages.c',
				'pages.h',
				'tree.h',
				'utils.c',
				'utils.h',
				'values.c',
				'values.h',
				'writer.c',
				'writer.h',
			],
		},
	]
}
