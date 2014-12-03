    $(document).ready(function(){
        $('#results').html('<p>Enter a search term to start filtering.</p>');

        $('#word').keyup(function() {

            var searchVal = $(this).val();
            if(searchVal !== '') {
                $.getJSON('../db/searchPoll.php?word='+searchVal, function(returnData) {
                    if (returnData.length == 0) {
                        $('#results').html('<p>Search term entered does not return any data.</p>');
                    } else {
                        var htmlR = '<h1> Results: </h1> </br><ul>';
                        for (var i = returnData.length - 1; i >= 0; i--) {
                            htmlR += '<li style="padding-left: 5px;">' + returnData[i] + '</li>';
                        };
                        $('#results').html(htmlR + '</ul>');
                    }
                });
            } else {
                $('#results').html('<p>Enter a search term to start filtering.</p>');
            }

        });

        $('#id').keyup(function() {

            var searchVal = $(this).val();
            if(searchVal !== '') {
                $.getJSON('../db/searchPoll.php?id='+searchVal, function(returnData) {
                 if (returnData.length == 0) {
                    $('#results').html('<p>Search term entered does not return any data.</p>');
                } else {
                    var htmlR = '<h1> Results: </h1> </br><ul>';
                    for (var i = returnData.length - 1; i >= 0; i--) {
                        htmlR += '<li style="padding-left: 5px;">' + returnData[i] + '</li>';
                    };
                    $('#results').html(htmlR + '</ul>');
                }
            });
            } else {
                $('#results').html('<p>Enter a search term to start filtering.</p>');
            }

        });

        $('#username').keyup(function() {

            var searchVal = $(this).val();
            if(searchVal !== '') {
                $.getJSON('../db/searchPoll.php?username='+searchVal, function(returnData) {
                    if (returnData.length == 0) {
                        $('#results').html('<p>Search term entered does not return any data.</p>');
                    } else {
                        var htmlR = '<h1> Results: </h1> </br><ul>';
                        for (var i = returnData.length - 1; i >= 0; i--) {
                            htmlR += '<li style="padding-left: 5px;">' + returnData[i] + '</li>';
                        };
                        $('#results').html(htmlR + '</ul>');
                    }
                });
            } else {
                $('#results').html('<p>Enter a search term to start filtering.</p>');
            }

        });

    });