$project_dir = File.dirname(__FILE__)
$task_dir    = File.expand_path('tools/rake', $project_dir)
$tmp_dir     = File.expand_path('tmp',        $project_dir)
$build_dir   = File.expand_path('build',      $tmp_dir)

Dir.glob(File.join($task_dir, '*.rake')).each { |task| load task }

def debug?
  return false
end

task :default => :build

