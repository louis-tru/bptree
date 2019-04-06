{
	'targets': [
		{
			'target_name': 'bplus-tree',
			'type': 'static_library',
			'include_dirs': [ 'include', ],
			'direct_dependent_settings': {
				'include_dirs': [ 'include', ],
			},
			'sources': [
				'include/bplus.h',
				'bplus.c',
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
