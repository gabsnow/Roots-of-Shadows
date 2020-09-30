<!--news.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: News page of the website for Roots of Shadows: every announcement by the developpers
	will be made here, updates of the game, release dates, etc. -->
<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - À propos</title>
	<meta charset="UTF-8">
	<meta http-equiv="Content-type" content="text/html; charset=UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
	<link rel="stylesheet" href="/public/css/all.min.css">
	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
	<link rel="stylesheet" type="text/css" href="/public/css/about.css">
</head>
<body>
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require_once("/$root/public/layout/topmenu.php");
	?>

	<div class="body">
		<div class="filterWrapper full-width min-full-height flex vertical font-white">
			<h1 class="centext">À propos</h1>
				<div class="flex horinzontal filterWrapper dark">
					<div class="flex big vertical about">
						<h1>Roots of Shadows</h1>

						<h2>Projet d'école</h2>
						<p>Roots of Shadows est un jeu de rôle de style médiéval développé dans le cadre du cours de projet en informatique de gestion au Collège Lionel-Groulx et supervisé par <b>Vincent Echelard</b>.</p>

						<p>Les technologies et langages utilisés pour le site web sont : une base de données MariaDB, HTML5 & CSS3, Javascript, jQuery et PHP. Plutôt que d'utiliser un framework pour le développement du site, nous avons préféré créer nous-même une structure MVC.</p>

						<p>Pour ce qui est du jeu en soi, nous utilisons le moteur de jeu Unreal Engine, qui nous permet de découvrir divers concepts et méthodes de programmation (blueprints, liaison d'événements, composants en C++, connection à une base de donnée). Le jeu est principalement conçu en C++, mis à part les éléments d'animations et l'interface graphique. C'est également nous-même qui avons conçu les différents niveaux du jeu (à l'aide d'assets).</p>

						<p>Nous avons choisi de construire un projet basé sur des concepts et outils avec lesquels nous ne sommes pas familiers dans le but de pousser les notions de programmation acquises lors de notre parcours en informatique de gestion. Il s'agissait pour nous d'une opportunité de découvrir des outils avec lesquels nous n'avons pas ou très peu travaillé.</p>

						<p>Pour plus d'informations sur les outils externes du projet ou sur les contributions personnelles à notre projet, rendez vous sur la page <a href="/credits">Credits</a>.</p>
						<br>

						<h2>Description</h2>

						<p>Roots of Shadows est un jeux de type RPG (jeu de rôle) dans une ère médiévale où il est possible de combattre des ennemis au corps à corps ou avec l’aide de certaines attaques spéciales, de remplir des quêtes et de monter de niveau afin d’être plus fort.</p>

						<p>Afin de pouvoir jouer au jeu et de pouvoir se créer un personnage, il faut s’inscrire à partir du site du jeu farseeds.ca. Lors de la première connexion à partir de l’interface du jeu, il faut choisir le nom de son personnage et créer celui-ci afin de commencer l’aventure. Sinon, nous continuons là où nous avons arrêté le jeu.</p>

						<p>Le jeu se déroule sur une île qui, à l’heure actuelle, est le seul endroit qui n’a pas été affecté par les ténèbres et les forces du mal. L’héroïne (le personnage joué par le joueur) doit faire son chemin dans sur cette île afin d’acquérir les compétences nécessaire pour défendre les innocents du mal. Afin de terminer le tutoriel du jeu, il faut compléter la quête principale qui guide le joueur à découvrir les personnages clés qui sont sur cette terre et à vaincre certains ennemis.</p>

						<br>

						<h2>Projet à long terme</h2>

						<p>FAR Seeds signifie <i>Fantastic and Realistic Seeds</i>, il s'agit (presque) du nom de l'entreprise que nous souhaitons mettre sur pied (dans un futur lointain). Cette entreprise œuvrerait dans la conception de jeux vidéo fantastiques en restant le plus réalistique possible (d'où le nom de l'entreprise!).</p>

						<p>La majorité des jeux de nos jours sortent tous du même moule, ce sont surtout des éléments comme la thématique, la musique, la qualité des graphiques, les interfaces utilisateurs et l'histoire mis en place qui changent. Ce que nous voulons faire de plus, c'est introduire des nouveaux concepts qui réinventeront complètement la structure des jeux tels que nous les connaissons. Des concepts qui, ultimement, créeront une impression d'immersion réelle. C'est justement sur tous les aspects qui sont négligés que nous souhaitons nous concentrer, aspects qui pointent presque tous vers le réalisme de l'univers du jeu au final.</p>
						<br><br>

						<h1>L'équipe</h1>

						<div class="flex horizontal filterWrapper team-box">

							<div class="flex vertical dev hugo">
								<div class="img-box medium">
									<img src="/public/images/dev-acideli.png">
								</div>
								<label class="lbl-title devs">Acideli</label>

								<div class="break">
									<a href="mailto:h_lamoureux@aol.com"><h4>Hugou Lamoureux</h4></a>
									<div class="centext">
										Level Designer
									</div>
									<div class="centext">
										Spécialiste des effets
									</div>
									<div class="centext">
										Conception & Developpement
									</div>
								</div>
							</div>

							<div class="flex vertical dev bruno">
								<div class="img-box medium">
									<img src="/public/images/dev-babou.jpg">
								</div>
								<label class="lbl-title devs">Babou</label>
								<div class="break">
									<a href="mailto:brugauthier@hotmail.com"><h4>Bruno Gauthier</h4></a>
									<div class="centext">
										Gestionnaire de BD
									</div>
									<div class="centext">
										Gestionnaire des événements
									</div>
									<div class="centext">
										Conception & Developpement
									</div>
								</div>
							</div>

							<div class="flex vertical dev oli">
								<div class="img-box medium">
									<img src="/public/images/dev-olivius.jpg">
								</div>
								<label class="lbl-title devs">Olivius Guyus</label>
								<div class="break">
									<a href="mailto:vikdreamz@gmail.com"><h4>Olivier Guy</h4></a>
									<div class="centext">
										Gestionnaire de BD
									</div>
									<div class="centext">
										Gestionnaire des interfaces
									</div>
									<div class="centext">
										Conception & Developpement
									</div>
								</div>
							</div>

							<div class="flex vertical dev gab">
								<div class="img-box medium">
									<img src="/public/images/dev-punzo.png">
								</div>
								<label class="lbl-title devs">Punzo</label>
								<div class="break">
									<a href="mailto:gabrielbourgeois1@hotmail.com"><h4>Gabriel Bourgeois</h4></a>
									<div class="centext">
										Administrateur web
									</div>
									<div class="centext">
										Gestionnaire du repo
									</div>
									<div class="centext">
										Conception & Developpement
									</div>
								</div>
							</div>
						</div>

					</div>
				</div>
			</div>
		</div>
	</div>

<?php require_once("$root/public/layout/footer.php"); ?>
</body>
</html>
