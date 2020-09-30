<!--credits.php
	Author: Gabriel Bourgeois
	Creation date: 14/06/19
	Last editted: 14/06/19
	Description: Credit page of the website for Roots of Shadows -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Credits</title>
	<meta charset="utf-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
		<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
		<link rel="stylesheet" type="text/css" href="/public/css/about.css">
</head>
<body>
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require_once("$root/public/layout/topmenu.php");
	?>

	<div class="body">
		<div class="filterWrapper full-width min-full-height flex vertical font-white">
			<h1 class="centext">Credits & Remerciements</h1>
				<div class="flex horinzontal filterWrapper dark">
					<div class="flex big vertical about">
						<h2>Remerciements</h2>

						<ul class="main-ul special-thanks">
							<li>Merci à <span class="thanks">Vincent Echelard</span> de nous avoir supervisé et nous avoir guidé tout au long du projet, sans qui nous aurions eu beaucoup de difficulté à savoir où s'enligner et à avoir les ressources nécessaires pour avancer avec Unreal Engine.</li>
							<li>Merci à <span class="thanks">François Jean</span> d'avoir accepté de nous partager les ateliers et les ressources de son cours sur Unreal Engine qu'il donnait au Collège les années précédentes, sans quoi nous n'aurions tout simplement pas pû travailler avec cet outil très large et parfois complexe.</li>
							<li>Merci à <span class="thanks">François Boileau</span> de nous avoir permis d'avoir un espace sur son site pendant l'été, ce qui nous à permis de prendre un peu d'avance sur le développement du site et de tester si tout allait bien.</li>
							<li>Merci à <span class="thanks">Saliha Yacoub</span> de nous avoir permis de garder notre accès à la base de données pendant l'été, ce qui nous a également permis de prendre de l'avance sur les éléments de la base de données et de faire des requêtes directement à partir du site que nous developpions.</li>
							<li>Merci à <span class="thanks">Alexandre André-L'espérance</span> de nous avoir donné les outils nécessaire pour la préparation de notre projet et également de nous avoir guidé tout au long du projet.</li>
							<li>Merci à <span class="thanks">Patrice Roy</span> de nous avoir aidé lors de nos difficulté avec les bases de données, il a su nous guider vers des ressources externes et nous a fait sauvé beaucoup de temps.</li>
							<li>Merci à <span class="thanks">Rachid Kadouche</span> de nous avoir aidé à comprendre les outils de connexions de bases de données écrites en C/C++ qui ne sont pas particulièrement simples à utiliser et que nous avions sous la main.</li>
						</ul>

						<p><u>Un gros merci à tous nos professeurs à Lionel-Groulx qui nous ont permis d'acquérir les connaissances nécessaires pour le développement du projet dans son ensemble.</u></p>

						<h2>Crédits</h2>
						<h4>Liste de toutes les technologies utilisées et des outils externes que nous n'avons pas conçus mais avec lesquels nous avons construit notre projet.</h4>

						<p>Technologies utilisées</p>
						<ul class="main-ul">
							<li>HTML</li>
							<li>CSS</li>
							<li>Javascript</li>
							<li>Amazon Web Services</li>
							<li>Unreal Engine</li>
							<li>C++</li>
							<li>Blueprints unreal</li>
							<li>MariaDB</li>
							<li>PHPMyAdmin</li>
							<li>Git</li>
							<li>Github</li>
						</ul>

						<p>Site web</p>
						<ul class="main-ul">
							<li>Îcones sur le site: <a href="https://fontawesome.com">Font Awesome</a> </li>
							<li>Patterns sur le site: <a href="https://www.toptal.com/designers/subtlepatterns/">Subtle Patterns</a> </li>
							<li>Gradients sur le site: <a href="https://uigradients.com/#Autumn">uiGradients</a> </li>
						</ul>

						<p>Jeu</p>
						<ul class="main-ul">
							<li>
								Assets de Paragon:
								<ul>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-aurora">Le personnage du joueur</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-gideon">Albus</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-iggy-scorch">Melee & Audace</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-revenant">Robert</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-sparrow">Jeane of Ark</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-boris">Woody</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-greystone">Escanor</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-rampage">Rampage</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-countess">Lilith</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/paragon-agora-and-monolith-environment">Monuments</a></li>
								</ul>
							</li>
							<li>
								Assets d'Infinity Blade
								<ul>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/infinity-blade-enemies">Adversaires</a></li>
									<li><a href="https://www.unrealengine.com/marketplace/en-US/slug/infinity-blade-effects">Effets</a></li>
								</ul>
							</li>
							<li>Assets d'<a href="https://www.unrealengine.com/marketplace/en-US/slug/open-world-demo-collection">Environnement</a></li>
							<li>Assets de <a href="https://www.unrealengine.com/marketplace/en-US/slug/advanced-village-pack">Village</a></li>
							<li>Assets d'<a href="https://www.unrealengine.com/marketplace/en-US/slug/17c2d7d545674204a7644c3c0c4c58ba">Adversaires animaux</a></li>
							<li>Assets d'<a href="https://www.unrealengine.com/marketplace/en-US/slug/7f7775996f7442b187f6fa510ec9d289">Adversaires fantastiques</a></li>
						</ul>

					</div>
				</div>
			</div>
		</div>
	</div>

	<?php require_once("$root/public/layout/footer.php"); ?>
</body>
</html>
