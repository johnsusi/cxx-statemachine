require 'fileutils'

task :clean do

  FileUtils.rm_rf($build_dir, :secure => true)

end

task :distclean do
  FileUtils.rm_rf($tmp_dir, :secure => true)
end
