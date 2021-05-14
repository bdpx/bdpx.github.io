
function autoheight(a) {
    if (!$(a).prop('scrollTop')) {
        do {
            var b = $(a).prop('scrollHeight');
            var h = $(a).height();
            $(a).height(h - 5);
        }
        while (b && (b != $(a).prop('scrollHeight')));
    };
    $(a).height( $(a).prop('scrollHeight') );
    $(a).width(400);
}


$( document ).ready(function() {

/*
$("textarea").each( function() {
   var id = $(this).attr('id');
   if( id ) {
     $.ajax({
        url: id,
        data: "",
        success: function(text) {
           alert('loaded ' + id + ' ' + text);
           var xxx = $('textarea[id="'+id +'"');
           xxx.text(text);
           CodeMirror.fromTextArea( xxx[0], {
               //value: text,
               lineNumbers : false, //true,
               matchBrackets : true,
               tabMode: "indent",
               viewportMargin:Infinity,
               readOnly: true,
               mode: "xml",
               htmlMode: false,
               theme : "material"
           });
           xxx[0].remove();
        },
        dataType: "text",
        async: false
     });
   }
});
*/

$("textarea.cpp").each( function () {
    var editor = CodeMirror.fromTextArea( $(this)[0], {
    //value: text,
    lineNumbers : false, //true,
    matchBrackets : true,
    mode: "text/x-c++src",
    tabMode: "indent",
    viewportMargin:Infinity,
    readOnly: true,
    theme : "material"
    });
});

$("textarea.xml").each( function () {
    var editor = CodeMirror.fromTextArea( $(this)[0], {
    //value: text,
    lineNumbers : false, //true,
    matchBrackets : true,
    tabMode: "indent",
    viewportMargin: Infinity,
    readOnly: true,
    mode: "xml",
    htmlMode: false,
    theme : "material",
    lineWrapping: true
    });
});

$("textarea.pascal").each( function () {
    var editor = CodeMirror.fromTextArea( $(this)[0], {
    //value: text,
    lineNumbers : false, //true,
    matchBrackets : true,
    tabMode: "indent",
    viewportMargin:Infinity,
    readOnly: true,
    mode: "text/x-pascal",
    htmlMode: false,
    theme : "material"
    });
});


});

