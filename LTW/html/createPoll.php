<?php
$dbh = new PDO('sqlite:../db/database.db');
$ip = 0;
if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
  $ip = $_SERVER['HTTP_CLIENT_IP'];
} elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
  $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
} else {
  $ip = $_SERVER['REMOTE_ADDR'];
}
$username = "Guest";

$userid = 0;

$stmt = $dbh->prepare('SELECT idUser, IPUser FROM UserLogin WHERE IPUser = ?');
$stmt->execute(array($ip));

while ($row = $stmt->fetch()) {
  if(in_array($ip, $row)) {
    $userid = $row['idUser'];
    $stmt1 = $dbh->prepare('SELECT username, idUser FROM User WHERE idUser = ?');
    $stmt1->execute(array($userid));
    while ($row1 = $stmt1->fetch()) {
      if(in_array($userid, $row1)) {
        $username = $row1['username'];
      }
    }
  }
}

?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script src="../resources/js/bootstrap.min.js"></script>
  <title>Pollerino</title>
  <link rel="shortcut icon" href="../resources/icon.ico"/>
  <meta charset="utf-8">
  <link rel="stylesheet" href="../resources/css/bootstrap.min.css">
  <link rel="stylesheet" href="../css/createPoll.css" hreflang="en">
</head>
<?php flush(); ?>
<body>
  <!--<?php  session_start();   $_SESSION['usernameOn'] = $username;  $_SESSION['ipOut'] = $ip; ?> -->
  <nav class="navbar navbar-default navbar-fixed-top" role="navigation">
  <div class="container-fluid">
    <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
      <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href="#">Brand</a>
    </div>

    <!-- Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
      <ul class="nav navbar-nav">
        <li class="active"><a href="#">Link <span class="sr-only">(current)</span></a></li>
        <li><a href="#">Link</a></li>
        <li class="dropdown">
          <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false">Dropdown <span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <li><a href="#">Action</a></li>
            <li><a href="#">Another action</a></li>
            <li><a href="#">Something else here</a></li>
            <li class="divider"></li>
            <li><a href="#">Separated link</a></li>
            <li class="divider"></li>
            <li><a href="#">One more separated link</a></li>
          </ul>
        </li>
      </ul>
      <form class="navbar-form navbar-left" role="search">
        <div class="form-group">
          <input type="text" class="form-control" placeholder="Search">
        </div>
        <button type="submit" class="btn btn-default">Submit</button>
      </form>
      <ul class="nav navbar-nav navbar-right">
        <li><a href="#">Link</a></li>
        <li class="dropdown">
          <a href="#" class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false">Dropdown <span class="caret"></span></a>
          <ul class="dropdown-menu" role="menu">
            <li><a href="#">Action</a></li>
            <li><a href="#">Another action</a></li>
            <li><a href="#">Something else here</a></li>
            <li class="divider"></li>
            <li><a href="#">Separated link</a></li>
          </ul>
        </li>
      </ul>
    </div><!-- /.navbar-collapse -->
  </div><!-- /.container-fluid -->
</nav>
  <div id ="container" class="container">
    <div class="flat-form">
      <ul class="tabs">
        <li>
          <p>Create Poll</p>
        </li>
      </ul>

      <div id="CreatPoll" class="form-action show">
        <h1>Creating Poll</h1>
        <form action="../db/newpoll.php" method="post">
          <ul>
            <p>
              Question:
            </p>
            <li>
              <input type="text" name="Question" placeholder="Question" required>
            </li>

            <p>
             <p>
              Image:
            </p>
            <li>
              <input type="text" name="queryImage" placeholder="Image" required>
            </li>

            <p>


              Options:
            </p>
            <p>
              <div id="dynamicInput">
                <script src="../js/createPoll.js" language="Javascript" type="text/javascript"></script>
                <div class="addtinput">
                <input type="text" name="inputs1" class="newOpt" placeholder="New Optionerino..."> 
                <input type="button" name="deleteInput1" class="buttonDel" value="−" onclick="deleteInput(this);">
                </div>
                <div class="addtinput">
                <input type="text" name="inputs2" class="newOpt" placeholder="New Optionerino..."> 
                <input type="button" name="deleteInput2" class="buttonDel" value="−" onclick="deleteInput(this);">
                </div>
              </div>
              <input type="button" value="Add another optionerino" class="buttonAdd" onClick="addInput('dynamicInput');">
            </p>
            <p>
              Private ? </br></br>
              <input type="checkbox" id="privacy" name="privacy" value="Yes" checked>
            </p>
            <p>
              Multiple Answers ? </br></br>
              <input type="checkbox" id="multiple" name="multiple" value="Yes" checked>
            </p>
            <p>
              <li>
                <input type="submit" value="Create" class="button" />
              </li>
            </p>
          </ul>
        </form>
      </div>
    </div>
  </div>
  <footer>
    <center> 2014 LTW  © All rights reserved to no one. </center>
  </br> <center> Pls no copy pasterino </center>
</footer>
</body>
</html>