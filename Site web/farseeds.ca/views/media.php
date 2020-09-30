<!--media.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Media page of the website for Roots of Shadows: the media page contains the artwork,
	sceenshots, wallpapers, videos of the game. -->

<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - Médias</title>
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
		require_once("/$root/public/layout/topmenu.php");
	?>

	<div class="body">
			<div class="filterWrapper full-width min-full-height flex vertical font-white">
				<h1 class="centext">Videos</h1>
					<div class="flex horinzontal filterWrapper dark">
						<div class="video-wrapper">
							<video width="1000" src="/public/videos/IntroSite.mp4" controls poster="/public/images/poster.jpg"></video>
						</div>
					</div>
					<h1 class="centext">Screenshots</h1>
					<div class="filterWrapper dark">

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Albus</div>
								<img src="/public/images/Albus.png">
								<div class="image-desc">
									Voici un grand magicien! Littéralement, il fait 8'5.
								</div>
							</div>

							<div class="image-wrapper">
								<div class="image-title">Escanor</div>
								<img src="/public/images/Escanor.png">
								<div class="image-desc">
									On raconte qu'il est le premier arrivé sur l'île, en théorie.
									En pratique, Boris était la bien avant lui.
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Boris</div>
								<img src="/public/images/Boris.png">
								<div class="image-desc">
									Boris était le premier arrivant de l'île. Cependant, personne n'as jamais remarqué
									sa présence parce qu'il était enfouis dans la forêt et abusait de son pouvoir d'hibernation.
									Jeanne l'as découvert 2ans après son arrivée.
								</div>
							</div>

							<div class="image-wrapper">
								<div class="image-title">Lilith</div>
								<img src="/public/images/Lilith.png">
								<div class="image-desc">
									Personne ne sais de quoi Lilith est faite. Certain raconte qu'elle serait en fait
									un amas de négativité et de poussière. Une chose est certaine, elle est la reine
									du chaos!
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Jeanne</div>
								<img src="/public/images/Jeanne.png">
								<div class="image-desc">
									Elle n'as beau avoir que 17 ans, Jeanne est une archère réputée. Elle a le potentiel
									de devenir une vraie héroine! D'après Escanor, son insouciance la conduira au bûcher.
								</div>
							</div>

							<div class="image-wrapper">
								<div class="image-title">Melee et Audace</div>
								<img src="/public/images/Melee&Audace.png">
								<div class="image-desc">
									Personne ne connaît vraiment l'origine de ces deux là. Ils sont arrivés un jour,
									et repartiront un autre jour, mais pour l'instant ils tiennent la meilleure taverne
									de l'île.
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Roger</div>
								<img src="/public/images/Roger.png">
								<div class="image-desc">
									Roger est un pêcheur. Certains lui reproche d'avoir l'air d'un tueur à
									gages, mais il jurera qu'il s'habille de cette manière dans le but d'attirer
									les requins plus facilement.
								</div>
							</div>
							</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Escaport</div>
								<img src="/public/images/Escaport.png">
								<div class="image-desc">
									Escaport est un village situé à l'ouest de l'île. Il a été nommé par Escanor
									en son propre honneur... Non mais! vous dites vous, pour qui se prend-il?!
								</div>
							</div>
						</div>


						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Hell Forge</div>
								<img src="/public/images/HellForge.png">
								<div class="image-desc">
									La seule personne à être sorti de Hell Forge vivant, c'est Personne. Personne ne connaît
									Personne sauf Personne et Nickolas Nicolsmith, un forgeron extrèmement agressif qui fait
									disparaître la plupart des gens qui s'approche de Hell Forge. Sauf Personne apparemment...
								</div>
							</div>
</div>
<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Last Hope</div>
								<img src="/public/images/LastHope.png">
								<div class="image-desc">
									C'est où Melee et Audace ont choisi d'installer leur taverne. Tous les soirs passé 21h,
									les villageois trinquent jusqu'au petites heures. Il n'est pas rare de voir des villageois
									ivre mort dormant au pied de la taverne. Une fois, on à même retrouvé le bûcheron du village
									dans le puis, c'est à ce demander ce que contient la bièrre...
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Wind Forest</div>
								<img src="/public/images/Woods.png">
								<div class="image-desc">
									Voici les bois où Jeanne à découvert Boris endormi. Cet endroit à une particularité bien étrange qui fait
									de Wind Forest une place très paisible: personne n'as encore émis de rumeur sur le lieu. Toutefois,
									si j'était vous, je ne parirais pas une seule citrouille la dessus!
								</div>
							</div>
							</div>
<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Burning Peak</div>
								<img src="/public/images/Volcan.png">
								<div class="image-desc">
									Burning Peak est un volcan en éruption depuis le début des temps. Du moins, c'est ce que
									Boris raconte. Selon Boris, le début des temps remonte à 20 ans en arrière. Donc, nous savons
									que le volcan est en éruption depuis 20 ans. En année d'ours, cela fait plus de... personne ne
									calcule en années d'ours, alors il faut demander à Boris, s'il n'hiberne pas.
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Lilith's Ground</div>
								<img src="/public/images/LilithsGround.png">
								<div class="image-desc">
									Lilith s'est appropriée cette petite île de l'archipel. Depuis son arrivée,
									l'eau à perdue sa teine bleu claire et tend vers le noire. D'après le fleuriste
									du village, Lilith serait les racines de cette ombre qui grandit sur l'île. Escanor,
									qui à la réponse à toute question, dilème et énigme, ne s'est toujours pas prononcé
									sur la théorie du fleuriste. Cela semble inquièter les villageois.
								</div>
							</div>
							</div>
<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Mystic Pouch</div>
								<img src="/public/images/Mysticpouch.png">
								<div class="image-desc">
									Albus est le seul habitant de cette île. Il à créer un portail magique
									pour permettre aux visiteurs d'accéder à son île pour avoir plus de compagnie,
									mais seule Jeanne lui rend visite une fois par année, au solstice d'été. À bien
									y penser, il doit y avoir une raison particulière...
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Sacred Hearth</div>
								<img src="/public/images/SacredHearth.png">
								<div class="image-desc">
									Sacred Hearth est le village de la renaissance. Plus petit qu'Escaport, Sacred Hearth
									Attire des villageois en quête de renouveau. Cependant, depuis quelques temps, les
									villageois ont déserté le village puisqu'une meute de loups s'est installée tout
									près.
								</div>
							</div>
							</div>
<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Shark Tides</div>
								<img src="/public/images/SharkTides.png">
								<div class="image-desc">
									C'est où Robert passe 99.9% de son temps. Il parvient à pêcher une quantitée astronomique
									de requins par jour, c'est ça seule mission. Même si les villageois ont peur de Robert à
									cause de son apparence de tueur en série, ils ne manquent jamais de nourriture.
								</div>
							</div>
						</div>

						<div class="flex horizontal centered">
							<div class="image-wrapper">
								<div class="image-title">Valley of Skulls</div>
								<img src="/public/images/ValleyOfSkulls.png">
								<div class="image-desc">
									Valley of Skulls porte bien son nom. Archimédoche, un archéologue bien ordinaire cherchait des
									vestiges du passé dans le but de clarifier sa thèse sur la poussée subie par les objets. Un jour il
									trouva un crâne. Puis 2, puis 144 000 précisément. Personne ne comprenait la corrélation entre la
									poussée subi et les crânes, et lui non plus probablement, puiqu'après sa découverte, il déserta l'île et
									on entendu plus jamais parler de lui. Peut-être avait-il réaliser quelque chose de beaucoup plus
									grand qu'une simple théorie sur la poussée universelle?
								</div>
							</div>

						</div>

					</div>
			</div>
	</div>

	<?php include_once("/$root/public/layout/footer.php"); ?>
</body>
</html>
