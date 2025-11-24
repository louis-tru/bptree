{
	'variables': {
		'use_qk_rwlock%': 0,
	},
	'targets': [
		{
			'target_name': 'bptree',
			'type': 'static_library',
			'include_dirs': [ 'include', ],
			'direct_dependent_settings': {
				'include_dirs': [ 'include', ],
			},
			'cflags': [ '-std=c99', '-pedantic', '-O3' ],
			'defines': [
				'_LARGEFILE_SOURCE',
				'_FILE_OFFSET_BITS=64',
				'_XOPEN_SOURCE=500',
				'_DARWIN_C_SOURCE',
			],
			'conditions': [
				['use_qk_rwlock==1', {
					'defines': [ '_USE_qk_rwlock=1' ],
				}, {
					'defines': [ '_USE_pthread_rwlock=1' ],
					'cflags': [ '-pthread' ],
					'ldflags': [ '-pthread' ],
				}],
			],
			'sources': [
				'include/bplus.h',
				'include/errors.h',
				'src/compressor.h',
				'src/pages.h',
				'src/tree.h',
				'src/utils.h',
				'src/values.h',
				'src/writer.h',
				'src/bplus.c',
				'src/pages.c',
				'src/utils.c',
				'src/values.c',
				'src/writer.c',
			],
		},
	]
}
