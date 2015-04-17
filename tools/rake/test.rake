task :test => :build do

  Dir.glob( File.join($build_dir, '**/test_*') ).each do |file|

    next if File.directory?(file)
    if (File.executable?(file)) then
      puts "Running #{ File.basename(file) }"
      puts '-' * 80
      start_time = Time.now
      system(file)
      end_time = Time.now
      puts '-' * 80
      puts "Time: #{'%.2f' % ((end_time - start_time) * 1000)} ms"

    end

  end


end
