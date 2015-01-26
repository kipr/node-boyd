{
  'targets': [
    {
      'target_name': 'node-boyd',
      'sources': [
        'node-boyd.cpp',
      ],
      'include_dirs': [],
      'link_settings': {
        'libraries': [
          '-lm',
          '-lopencv_core',
          '-lopencv_videoio',
          '-lopencv_imgcodecs',
        ],
        'library_dirs': [
          '/usr/lib',
          '/usr/local/lib',
        ],
      },
      "conditions": [
        [ 'OS=="mac"', {
            'xcode_settings': {
              'GCC_ENABLE_CPP_EXCEPTIONS': 'YES',
              'OTHER_CFLAGS': [ '-g', '-mmacosx-version-min=10.7', '-std=c++11', '-stdlib=libc++', '-O3', '-D__STDC_CONSTANT_MACROS', '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE', '-Wall' ],
              'OTHER_CPLUSPLUSFLAGS': [ '-g', '-mmacosx-version-min=10.7', '-std=c++11', '-stdlib=libc++', '-O3', '-D__STDC_CONSTANT_MACROS', '-D_FILE_OFFSET_BITS=64', '-D_LARGEFILE_SOURCE', '-Wall' ]
            }
        }]
      ]
    }
  ]
}