<!-- topmenu.php
Author: Gabriel Bourgeois
Created: 14/06/19
Last edited: 14/07/10 (Hugo)
Description: Layout (top menu) of the website -->

<link rel="stylesheet" href="/public/css/topmenu.css">

<header>
  <nav>
    <ul id="TopMenu">
      <div id="TopLeftMenu">
        <li>
          <a href="/home">
            <i class="fas fa-home"></i>
            <span>Accueil</span>
          </a>
        </li>
        <li>
          <a href="/lore">
            <i class="fab fa-fort-awesome"></i>
            <span>Histoire</span>
          </a>
        </li>
        <li>
          <a href="/media">
            <i class="fas fa-photo-video"></i>
            <span>Médias</span>
          </a>
        </li>
        <li>
          <a href="/news">
            <i class="far fa-newspaper"></i>
            <span>Nouvelles</span>
          </a>
        </li>
        <li>
          <a href="/download">
            <i class="fas fa-download"></i></i>
            <span>Téléchargement</span>
          </a>
        </li>
      </div>
      <div id="TopCenterMenu">
        <li>
          <img src="/public/images/roots_logo.png" alt="Roots of Shadows icon"/>
        </li>
      </div>
      <?php if(isset($_SESSION["username"])){
        echo "<div id='TopRightMenu'>
          <li>
            <a href='/account'>
              <span>Mon compte</span>
            </a>
          </li>
          <li>
            <a href='/logout'>
              <span>Déconnexion</span>
            </a>
          </li>
        </div>";
      }
      else{
        echo "<div id='TopRightMenu'>
          <li>
            <a href='/login'>
              <span>Connexion</span>
            </a>
          </li>
          <li class='bg-red'>
            <a href='/subscribe'>
              <span>Créer un compte!</span>
            </a>
          </li>
        </div>";
      } ?>

    </ul>
  </nav>
</header>
