
import "/js/jquery.js"
import "/codemirror/codemirror.js"
// import languages
import "/codemirror/mode/clike/clike.js"
import "/codemirror/mode/xml/xml.js"
import "/codemirror/mode/javascript/javascript.js"

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

function add_css_file(href) {
    // Create new link Element
    let link = document.createElement('link');
    // set the attributes for link element
    link.rel = 'stylesheet';
    link.type = 'text/css';
    link.href = href;
    // Get HTML head element to append link element to it
    document.getElementsByTagName('head')[0].appendChild(link);
}

$(document).ready(function() {
    // link CSSs
    add_css_file('/codemirror/codemirror.css');
    add_css_file('/codemirror/theme/3024-day.css');

    $('textarea[class=cpp]').each(function() {
        $(this).prop('readonly', true);
        var editor = CodeMirror.fromTextArea(this, {
            mode: "text/x-c++src",
            lineNumbers: false,
            lineWrapping: true,
            viewportMargin: Infinity,
            scrollbarStyle: "null",
            readOnly: true,
        });
        editor.save();
    });

    $('textarea[class=java]').each(function() {
        $(this).prop('readonly', true);
        var editor = CodeMirror.fromTextArea(this, {
            mode: "text/x-java",
            lineNumbers: false,
            lineWrapping: true,
            viewportMargin: Infinity,
            scrollbarStyle: "null",
            readOnly: true,
        });
        editor.save();
    });

    $('textarea[class=javascript]').each(function() {
        $(this).prop('readonly', true);
        var editor = CodeMirror.fromTextArea(this, {
            mode: "javascript",
            lineNumbers: false,
            lineWrapping: true,
            viewportMargin: Infinity,
            scrollbarStyle: "null",
            readOnly: true,
        });
        editor.save();
    });

    $('textarea[class=xml]').each(function() {
        $(this).prop('readonly', true);
        var editor = CodeMirror.fromTextArea(this, {
            mode: "xml",
            lineNumbers: false,
            lineWrapping: true,
            viewportMargin: Infinity,
            scrollbarStyle: "null",
            readOnly: true,
        });
        editor.save();
    });

    $('textarea[class=listing]').each(function() {
        $(this).prop('readonly', true);
        $(this).css('height', 'auto');
    });

    $('.CodeMirror').css('height', 'auto');
});
