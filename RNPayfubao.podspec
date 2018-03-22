
Pod::Spec.new do |s|
  s.name         = "RNPayfubao"
  s.version      = "1.0.0"
  s.summary      = "RNPayfubao"
  s.homepage     = "https://github.com/canyara/react-native-payfubao"
  s.license      = "MIT"
  # s.license      = { :type => "MIT", :file => "FILE_LICENSE" }
  s.author             = { "canyara" => "canyara@gmail.com" }
  s.platform     = :ios, "7.0"
  s.source       = { :git => "https://github.com/canyara/react-native-payfubao.git", :tag => "master" }
  s.source_files  = "RNPayfubao/**/*.{h,m}"
  #s.requires_arc = true
  s.preserve_paths  = "**/*.js"
  s.ios.vendored_frameworks = "Libs/JSProSDK.framework"
  #s.ios.frameworks    = "SystemConfiguration", "Security"
  #s.ios.library = 'z', 'c++'

  #s.dependency "React"
  #s.dependency "others"
end
