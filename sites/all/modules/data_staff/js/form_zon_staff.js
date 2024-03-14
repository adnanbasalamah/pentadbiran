jQuery(function ($) {
  $('.checkdel').on('change', function (e) {
    var SplitId = $(this).attr('id').split('-');
    if (this.checked) {
      $('#delete-' + SplitId[1]).val(1);
    } else {
      $('#delete-' + SplitId[1]).val(0);
    }
  });
});
