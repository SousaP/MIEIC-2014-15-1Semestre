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

	$.post("../db/newVote.php", {'idQuery' : idQuery, 'OptionX' : OptionX , 'Username' : username});
	location.reload(true);
}

function  OptionsReceived(data) {
	$.each(data, resultOptions);

	var but = document.createElement('input');
	but.setAttribute('type', 'button');
	but.setAttribute('value', 'Confirm answer');
	but.setAttribute('class', 'button');
	but.setAttribute('onClick', 'sendVote( \'<?= $idPoll?>\', \'<?= $username ?>\');');
	document.getElementById('dynamicOptions').appendChild(but);
}

// Called for each line received
function resultOptions(index, value) {
	seeOptions = 1;
	var radioHtml = value +'<input type="radio" name="Vote"';
	radioHtml += 'value="' + value + '"'
	radioHtml += '/>';
	var radioFragment = document.createElement('div');
	radioFragment.setAttribute('class', 'radio');
	radioFragment.innerHTML = radioHtml;

	document.getElementById('dynamicOptions').appendChild(radioFragment);

	return radioFragment.firstChild;
}

function init(seeOptions, idQuery) {
	if(seeOptions == 0) {
		$.getJSON("../db/getAnswers.php", {'idQuery' : idQuery}, OptionsReceived);
	}
}
