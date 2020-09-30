<!-- error.php
     author: Gabriel Bourgeois
     creation date: 09/08/2019
     description: error template page to display elegantly (eventually) errors
     throughout the dashboard -->

<!DOCTYPE html>
<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <title><?=$errorTitle?></title>
    <link rel="stylesheet" type="text/css" href="/public/css/all.min.css">
    <link rel="stylesheet" href="/public/css/globalstyle.css">
    <script type="text/javascript" src="/public/js/functions.js"></script>
  </head>
  <body>
    <div class="body">
      <div class="filterWrapper dark font-white">
        <h1>Error</h1>
        <p><?=$errorMessage?></p>
      </div>
    </div>
  </body>
</html>
