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
      }
    }
  ]
}