jQuery(function ($) {
   $('.zon-select').on('change', function (e){
      e.preventDefault();
      var request = new Object;
      var SplitId = $(this).attr('id').split('-');
      var IdxObj = SplitId[2];
      request.zone = $(this).val();
      var that = this;
      var AjaxAddress = Drupal.settings.basePath + 'masterdata/negeri/getajax';
      $.ajax({
         url: AjaxAddress,
         type: 'POST',
         data: request,
         dataType: 'json',
         success: function (data) {
            var returnData = eval(data);
            if (returnData){
               var IdNegeriAttr = '#negeri-tempatkegiatan-'+ IdxObj;
               $(IdNegeriAttr).select2('destroy');
               $(IdNegeriAttr).empty();
               for (key in returnData){
                  $(IdNegeriAttr).append('<option value="'+ key +'">'+ returnData[key] +'</option>');
               }
               $(IdNegeriAttr).select2();
            }else{
               $(IdNegeriAttr).empty();
            }
         }
      });
   });
});