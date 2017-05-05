(function ($) {
    $(function () {
        $('.tripal-feature-jbrowse-delete').click(function (e) {
            if (!confirm('Are you sure you want to delete this link?')) {
                e.preventDefault();
            }
        });
    });
})(jQuery);