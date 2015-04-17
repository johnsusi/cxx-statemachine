require 'fileutils'

task :cmake => 'cmake:build'

namespace :cmake do

  def ninja?
    return system("ninja --version")
  end

  def mingw?
    return system("mingw32-make --version")
  end

  def make?
    return system("make --version")
  end

  task :configure do

    configure
  end

  def configure
    return if File.directory?($build_dir)

    FileUtils.mkdir_p($build_dir)

    Dir.chdir($build_dir) do
      extra = ''
      extra << " -GNinja" if ninja?
      extra << " -DCMAKE_BUILD_TYPE=Debug" if debug?
      system("cmake #{$project_dir}#{extra}")
    end

  end

  task :build => :configure do
    system("cmake --build #{$build_dir}")
  end

end

