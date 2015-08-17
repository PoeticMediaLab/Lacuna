var gulp = require('gulp');
var sourcemaps = require('gulp-sourcemaps');
var babel = require('gulp-babel');
var watch = require("gulp-watch");
var plumber = require("gulp-plumber");

gulp.task('default', function () {
    return gulp.src('src/**/*.js')
        .pipe(plumber())
        .pipe(watch("src/**/*.js"))
        .pipe(sourcemaps.init())
        .pipe(babel({
            blacklist: ["useStrict"]
        }))
        .pipe(sourcemaps.write('.'))
        .pipe(gulp.dest('extapp'));
});