{
  'targets': [
    {
      'target_name': 'node-boyd',
      'sources': [
        'node-boyd.cpp', 'base64.cpp'
      ],
      'include_dirs': [],
      'link_settings': {
        'libraries': [
          '-lm',
          '-lopencv_core',
          '-lopencv_videoio',
          '-lopencv_imgcodecs',
          '-lopencv_imgproc',
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
            },
            'library_dirs': [
              '/usr/lib',
              '/usr/local/lib',
            ],
            'link_settings': {
              'libraries': [
                '-lm',
                '-lopencv_core',
                '-lopencv_videoio',
                '-lopencv_imgcodecs',
                '-lopencv_imgproc',
              ]
			}
        }],
        [ 'OS=="win"', {
            "configurations": {
              'Release': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    'AdditionalIncludeDirectories': ['$(OPENCV_DIR)\\..\\..\\include'],
                    'WarningLevel': 4,
                    'ExceptionHandling': 1,
                    'DisableSpecificWarnings': [4100, 4127, 4201, 4506]
                  },
                  'VCLinkerTool': {
                    'AdditionalLibraryDirectories': ['$(OPENCV_DIR)\\lib'],
                    'AdditionalDependencies': [
                      'opencv_core300.lib',
                      'opencv_videoio300.lib',
                      'opencv_imgcodecs300.lib',
                      'opencv_imgproc300.lib'
                    ]
                  }
                }
              },
              'Debug': {
                'msvs_settings': {
                  'VCCLCompilerTool': {
                    'AdditionalIncludeDirectories': ['$(OPENCV_DIR)\\..\\..\\include'],
                    'WarningLevel': 4,
                    'ExceptionHandling': 1,
                    'DisableSpecificWarnings': [4100, 4127, 4201, 4506]
                  },
                  'VCLinkerTool': {
                    'AdditionalLibraryDirectories': ['$(OPENCV_DIR)\\lib'],
                    'AdditionalDependencies': [
                      'opencv_core300.lib',
                      'opencv_videoio300.lib',
                      'opencv_imgcodecs300.lib',
                      'opencv_imgproc300.lib'
                    ]
                  }
                }
              }
            }
        }]
      ]
    }
  ]
}
