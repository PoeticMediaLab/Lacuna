module.exports = function(grunt) {
  grunt.initConfig({
  	coffee: {
		compile: {
				files: [{
					expand: true,
					cwd:'sites/all/modules/custom/',
					src: '**/*.coffee',
					dest: 'sites/all/modules/custom/',
					ext: ".js"
				}]
  		}
  	},
    watch: {
      files: ['sites/all/modules/custom/**/*.coffee'],
      tasks: ['newer:coffee:compile'],
      options: {
        livereload: true
      }
    }
  });

  grunt.loadNpmTasks('grunt-newer');
  grunt.loadNpmTasks('grunt-contrib-coffee');
  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.registerTask('default', ['watch']);
}




