function searchPolls()
{
	var elem = document.getElementById('dynamicSearch');
	var h1 = document.createElement('H1');
	var tE = document.createTextNode('My Polls: ');
	var ul = document.createElement('ul');
	ul.setAttribute('id', 'pollList');
	h1.appendChild(tE);
	elem.appendChild(h1);
	elem.appendChild(ul);
	elem.appendChild(document.createElement('br'));
	elem.appendChild(document.createElement('br'));
	console.log(search_p());
	search_p();
}

function search_p() {
	$.getJSON("../db/getPolls.php", PollsReceived);
}

// Called when messages are received
function  PollsReceived(data) {
	$.each(data, resultPoll);
}

// Called for each line received
function resultPoll(index, value) {
	var elem = document.getElementById('pollList');
	var li = document.createElement('li');
	var a = document.createElement('a');
	var linkText = document.createTextNode(value);
	a.appendChild(linkText);
	a.title = value;
	a.href = "../db/poll.php?Question=" + value;
	li.appendChild(a);
	elem.appendChild(li);
	elem.appendChild(document.createElement('br'));
}