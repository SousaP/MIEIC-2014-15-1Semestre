<?php
    $dbh = new PDO('sqlite:../db/database.db');
    $dbh->setAttribute( PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION );

?>

<html lang="en">
<head>
  <script src="../resources/jquery-1.9.1.js"></script>
  <script type="text/javascript" src="../js/poll.js"></script>
   <title>Pollerino</title>
   <link rel="shortcut icon" href="../resources/icon.ico"/>
        <meta charset="utf-8">
        <link rel="stylesheet" href="../css/poll.css" hreflang="en">
</head>
<body>
    <div class="Logout">
        <form action="logout.php" method="post">
            <ul class="Logout"> 
                <li>
                     <p>Username</p>
                </li>
                <li>
                     <input type="submit" value="Log Out" class="buttonOut" />
                </li>
            </ul>         
            </form>
        </div>
    <div id ="container" class="container">
        <div class="flat-form">
            <ul class="tabs">
                <li>
                    <a href="#CreatPoll" class="active">Create Poll</a>
                </li>
                <li>
                    <a href="#SearchPoll">Search Poll</a>
                </li>
                <li>
                    <a href="#Poll">Search Poll</a>
                </li>
            </ul>

            <div id="CreatPoll" class="form-action hide">
                <h1>Creating Poll</h1>
                <form method="post">
                    <ul>
                        <p>
                    Question?
                </p>
                        <li>
                            <input type="text" name="usernameL" placeholder="Question" required>
                        </li>

                         <p>
                    Options:
                </p>
                        <li>
                            <input type="text" name="option1" placeholder="Option 1" required>
                        </li>
                        <li>
                            <input type="text" name="option2" placeholder="Option 2" required>
                        </li>
                        <li>
                            <input type="text" name="option3" placeholder="Option 3" >
                        </li>
                        <li>
                            <input type="text" name="option4" placeholder="Option 4" >
                        </li>
                        <li>
                            <input type="submit" value="Creat" class="button" />
                        </li>
                    </ul>
                </form>

            </div>

            <div id="Poll" class="form-action hide">
                <h1>Searching for Poll</h1>
                <p>
                    Give key words / Id's / Username
                </p>
                <form>
                    <ul>
                        <li>
                            <input type="text" name="kWord" placeholder="Key Word" >
                        </li>
                         <li>
                            <input type="text" name="searchID" placeholder="ID" >
                        </li>
                        <li>
                            <input type="text" name="SearchUser" placeholder="Username" >
                        </li>
                        <li>
                            <input type="submit" value="Search" class="button" />
                        </li>
                    </ul>
                </form>
            </div>

            <div id="Poll" class="form-action show">
                <h1>Poll</h1>
                <form>
                    <ul>
                        <li>
                            <button>Update</button>
                            <div id="vis"></div>
                        </li>
                    </ul>
                </form>
            </div>

        </div>
    </div>
    <footer>
           <center> 2014 LTW  © All rights reserved to no one. </center>
        </footer>
</body>
</html>