<?php
    $dbh = new PDO('sqlite:../db/database.db');

    $query =  $_GET['Question'];

    $stmt = $dbh->prepare('SELECT idUserQuery, idUser FROM UserQuery WHERE Question = ?');
    $stmt->execute(array($query));
    $temp = $stmt->fetch();

    $idQ =$temp['idUserQuery'];
    $idU = $temp['idUser'];


    $ip = 0;
    if (!empty($_SERVER['HTTP_CLIENT_IP'])) {
            $ip = $_SERVER['HTTP_CLIENT_IP'];
        } elseif (!empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
            $ip = $_SERVER['HTTP_X_FORWARDED_FOR'];
        } else {
        $ip = $_SERVER['REMOTE_ADDR'];
    }

    
    $stmt1 = $dbh->prepare('SELECT idUser FROM UserLogin WHERE IPUser = ?');
    $stmt1->execute(array($ip));

    if($row = $stmt1->fetch()){
        
        if($idU === $row['idUser'])
            {
                header( 'Location: ../html/managePoll.php?idUserQuery='.$idQ);
        exit();
    }
        
    }
     header( 'Location: ../html/poll.php?idUserQuery='.$idQ);
     exit();

?>