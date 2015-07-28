(function($){

    Drupal.behaviors.CToolsAutoSubmit = {
        attach: function(context) {
            // 'this' references the form element
            function triggerSubmit (e) {
                var $this = $(this);
                if (!$this.hasClass('ctools-ajaxing')) {
                    $this.find('.ctools-auto-submit-click').click();
                }
            }

            // the change event bubbles so we only need to bind it to the outer form
            $('form.ctools-auto-submit-full-form', context)
                .add('.ctools-auto-submit', context)
                .filter('form, select, input:not(:text, :submit)')
                .once('ctools-auto-submit')
                .change(function (e) {
                    // don't trigger on text change for full-form
                    if ($(e.target).is(':not(:text, :submit, .ctools-auto-submit-exclude)')) {
                        triggerSubmit.call(e.target.form);
                    }
                });

            // e.keyCode: key
            var discardKeyCode = [
                16, // shift
                17, // ctrl
                18, // alt
                20, // caps lock
                33, // page up
                34, // page down
                35, // end
                36, // home
                37, // left arrow
                38, // up arrow
                39, // right arrow
                40, // down arrow
                9, // tab
                13, // enter
                27  // esc
            ];
            // Don't wait for change event on textfields
            $('.ctools-auto-submit-full-form input:text, input:text.ctools-auto-submit', context)
                .filter(':not(form-item-search-api-views-fulltext input)')
                .once('ctools-auto-submit', function () {
                    // each textinput element has his own timeout
                    var timeoutID = 0;
                    $(this)
                        .bind('keydown keyup', function (e) {
                            if ($.inArray(e.keyCode, discardKeyCode) === -1) {
                                timeoutID && clearTimeout(timeoutID);
                            }
                        })
                        .bind('change', function (e) {
                            if ($.inArray(e.keyCode, discardKeyCode) === -1) {
                                timeoutID = setTimeout($.proxy(triggerSubmit, this.form), 500);
                            }
                        });
                });
        }
    }

})(jQuery);