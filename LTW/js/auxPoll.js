var multiple = 0;

function sendVote(idQuery, username){
	var rates =  document.getElementsByName('Vote');
	var OptionX= '';
	for(var i = 0; i < rates.length; i++){
		if(rates[i].checked){
			OptionX = rates[i].value;
		}
	}
	if(OptionX == '')
	{
		alert('Select one option');
		return;
	}

	$.post("../db/newVote.php", {'idQuery' : idQuery, 'OptionX' : OptionX , 'Username' : username}, location.reload(true));
}

function  OptionsReceived(data) {
	$.each(data, resultOptions);
}

// Called for each line received
function resultOptions(index, value) {
	seeOptions = 1;
	if(multiple == 0)
		var radioHtml = value +'<input type="radio" name="Vote"';
	else
		var radioHtml = value +'<input type="checkbox" name="Vote"';
	radioHtml += 'value="' + value + '"'
	radioHtml += '/>';
	var radioFragment = document.createElement('div');
	radioFragment.setAttribute('class', 'radio');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicOptions').appendChild(radioFragment);

	return radioFragment.firstChild;
}

function initMultiple(data){
	console.log(data);
	multiple = data;
}

function init(seeOptions, idQuery) {
	if(seeOptions == 0) {
		$.get("../db/getPolltype.php",{'idQuery' : idQuery},initMultiple);
		$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
	}
}
