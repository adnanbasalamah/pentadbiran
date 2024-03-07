jQuery(function ($) {
  var AlamatGetKawasan = Drupal.settings.basePath + "masterdata/kawasan/getajax";
  var AlamatGetPremis = Drupal.settings.basePath + "masterdata/premis/getajax";
  $(".select-zon").on("change", function (e) {
    var split_id = $(this).attr("id").split("-");
    var kawasan_id = "";
    var premis_id = "";
    for (var i = 0;i < split_id.length;i++){
      if (split_id[i] === "zon"){
        kawasan_id += "-kawasan";
        premis_id += "-premis";
      }else{
        if (kawasan_id === ""){
          kawasan_id = split_id[i];
          premis_id = split_id[i];
        }else {
          kawasan_id += "-" + split_id[i];
          premis_id += "-" + split_id[i];
        }
      }
    }
    var selected_zon = $(this).val();
    var request = new Object;
    request.id_zon = selected_zon;
    request.chosen_input = true;
    $.ajax({
      url: AlamatGetKawasan,
      type: "GET",
      data: request,
      dataType: "json",
      success: function (data) {
        var returnData = eval(data);
        if (returnData) {
          $("#"+ kawasan_id).select2("destroy");
          $("#"+ kawasan_id).empty();
          var key = 0;
          $("#"+ kawasan_id).append("<option value=\"" + key + "\">TIADA KAWASAN</option>");
          for (key in returnData) {
            $("#"+ kawasan_id).append("<option value=\"" + key + "\">" + returnData[key] + "</option>");
          }
          $("#"+ kawasan_id).select2({ width: "130px" });
        } else {
          $("#"+ kawasan_id).empty();
        }
      }
    });
    $.ajax({
      url: AlamatGetPremis,
      type: "GET",
      data: request,
      dataType: "json",
      success: function (data) {
        var returnData = eval(data);
        if (returnData) {
          $("#"+ premis_id).select2("destroy");
          $("#"+ premis_id).empty();
          var key = 0;
          $("#"+ premis_id).append("<option value=\"" + key + "\">TIADA PREMIS</option>");
          for (key in returnData) {
            $("#"+ premis_id).append("<option value=\"" + key + "\">" + returnData[key] + "</option>");
          }
          $("#"+ premis_id).select2({ width: "130px" });
        } else {
          $("#"+ premis_id).empty();
        }
      }
    });
  });
});
