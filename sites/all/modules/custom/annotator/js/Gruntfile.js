module.exports = function(grunt) {
  grunt.initConfig({
    watch: {
      files: ['gruntfile.js', 'sites/all/modules/custom/**/*.coffee']
    },
    replacements: [{
      from: '/^(function() {/',
        to: '(function($) {'
      }, {
      from: '/^}).call(this);$/'
        to: '})(jQuery);',
      }
  });
}
