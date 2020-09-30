<!--subscribe.html
	Author: Gabriel Bourgeois
	Creation date: 13/06/19
	Last editted: 13/06/19
	Description: Subscription page of the website for Roots of Shadows -->

<!-- FUNCTIONS -->
<?php
	function validateName($name) {
		return preg_match("/^([^0-9]{2,18})$/", $name);
	}
	function validateDate($day, $month, $year) {
		return checkdate($month, $day, $year);
	}
	function validateUsername($username) {
		return preg_match("/^[a-zA-Z0-9]{6,18}$/", $username);
	}
	function validateEmail($email) {
		return preg_match("/^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$/", $email);
	}
	function validatePassword($password) {
		return preg_match("/^.{4,18}$/", $password);
	}

	function validatePasswordConfirmation($password, $confirm) {
		return $password === $confirm;
	}

	function validateSecurityQuestion($question) {
		return preg_match("/^.{4,60}$/", $question);
	}

	function validateSecurityAnswer($answer) {
		return preg_match("/^.{1,60}$/", $answer);
	}

	function userExists($username) {
		$servername = "167.114.152.54";
		$dbusername = "equipe46";
		$dbpassword = "6s89yux4";
		$conn = new PDO("mysql:host=$servername;dbname=dbequipe46", $dbusername, $dbpassword);

		//////////////////////////////////////////////////////////////////////////////////////
		// Check if user exists
		//////////////////////////////////////////////////////////////////////////////////////
		$stmt = $conn->prepare("CALL ROS_UserExists(?)");
		$stmt->bindParam(1, $username);
		$stmt->execute();

		$userExists = false;
		while($result = $stmt->fetch())
			$userExists = $result[0] > 0;

		$stmt->closeCursor();
		$conn = null;

		return $userExists;
	}
	function emailExists($email) {
		$servername = "167.114.152.54";
		$dbusername = "equipe46";
		$dbpassword = "6s89yux4";
		$conn = new PDO("mysql:host=$servername;dbname=dbequipe46", $dbusername, $dbpassword);

		//////////////////////////////////////////////////////////////////////////////////////
		// Check if email exists
		//////////////////////////////////////////////////////////////////////////////////////
		$stmt = $conn->prepare("CALL ROS_EmailExists(?)");

		$email = $_POST["email"];
		$stmt->bindParam(1, $email);

		$stmt->execute();

		$emailExists = false;
		while($result = $stmt->fetch())
			$emailExists = $result[0] > 0;

		return $emailExists;
	}

	function multi_strpos($haystack, $needles) {
 		foreach ($needles as $n)
		    if (strpos($haystack, $n, $offset) !== false)
				    return true;

 		return false;
 	}
?>

<?php
	if($_SERVER["REQUEST_METHOD"] == "POST") {
		$fill['firstName'] = $_POST["firstName"];
		$fill['lastName'] = $_POST["lastName"];
		$fill['birthDay'] = $_POST["birthDay"];
		$fill['birthMonth'] = $_POST["birthMonth"];
		$fill['birthYear'] = $_POST["birthYear"];
		$fill['username'] = $_POST["username"];
		$fill['email'] = $_POST["email"];
		$fill['password'] = $_POST["password"];
		$fill['confirmPassword'] = $_POST["confirmPassword"];
		$fill['securityQuestion'] = $_POST["securityQuestion"];
		$fill['securityAnswer'] = $_POST["securityAnswer"];
	}
?>


<!DOCTYPE html>
<html>
<head>
	<title>Roots of Shadows - New account</title>
	<meta charset="utf-8">
  	<meta name="viewport" content="width=device-width, initial-scale=1">
		<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
		<link rel="stylesheet" href="/public/css/all.min.css">
  	<link rel="stylesheet" type="text/css" href="/public/css/globalstyle.css">
</head>
<body>
	<!-- Top Menu -->
	<?php
		$root = realpath($_SERVER["DOCUMENT_ROOT"]);
		require_once("$root/public/layout/topmenu.php");
	?>

	<div class="body">
		<div class="form form-subscribe filterWrapper dark">
			<div class="img-box img-form">
				<img src="/public/images/roots_logo.png">
			</div>
			<form id="FormSubscribe" method="POST" action="subscribe.php" >
				<div class="flexput">
					<input id="newFirstName" type="text" name="firstName" class="field shared" placeholder="First name" required  pattern="[^0-9]{2,18}" title="First name must be between 2 and 18 characters and contain no number." autofocus value="">
					<input id="newLastName" type="text" name="lastName" class="field" placeholder="Last name" required pattern="[^0-9]{2,18}" title="First and Last name must be between 2 and 18 characters and contain no number." value="">
				</div>

				<!-- First and last name warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {
						if (!validateName($_POST["firstName"]) || !validateName($_POST["lastName"])) { ?>
							<div class="warning">
								<i class="fas fa-exclamation-triangle"></i>
								<span>First and last name must be between 2 and 18 characters and contain no number.</span>
							</div> <?php
		 				}
					}
				?>

				<div class="flexput">
					<!-- Birth day -->
					<input id="newBirthDay" type="number" name="birthDay" class="field first" placeholder="Birth day" required min="1" max="31" value="">

					<!-- Month -->
					<div id="newBirthMonth" class="select-container">
						<select name="birthMonth" required placeholder="month" class="field">
							<option value="" disabled selected><span>Month</span></option>
							<option value="1">January</option>
							<option value="2">February</option>
							<option value="3">March</option>
							<option value="4">May</option>
							<option value="6">June</option>
							<option value="7">July</option>
							<option value="8">August</option>
							<option value="9">September</option>
							<option value="10">October</option>
							<option value="11">November</option>
							<option value="12">December</option>
						</select>
					</div>

					<!-- Year -->
					<input id="newBirthYear" type="number" name="birthYear" class="field" placeholder="Year" min="1900" max="2019" required value="">
				</div>

				<!-- Date of birth warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>

				<!--<br>-->
				<input id="newUsername" type="text" name="username" class="field" placeholder="Username" required pattern="^[a-zA-Z0-9]{6,18}$" title="Username must be between 6 and 18 characters and contain no special character, example: DoctorBeaver." value="">

				<!-- User warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>

				<input id="newEmail" type="email" name="email" class="field" placeholder="Email" required pattern="^[a-z0-9._%+-]+@[a-z0-9.-]+\.[a-z]{2,4}$" title="Enter a valid email, example: doctorbeaver@rootsofshadows.com." value="">

				<!-- Email warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>

				<input id="newPassword" type="password" name="password" class="field" placeholder="Password" required pattern=".{4,18}" title="Password must be between 4 and 18 characters." value="">

				<!-- Password warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>

				<input id="newConfirmPassword" type="password" name="confirmPassword" class="field" placeholder="Confirm password" required pattern=".{4,18}" title="Password must be between 4 and 18 characters." value="">

				<!-- Password confirmation warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>

				<!--<br>-->
				<input id="newSecurityQuestion" type="text" name="securityQuestion" class="field" placeholder="Security question" required pattern=".{4,60}" title="Security question must be between 4 and 60 characters." value="">

				<!-- Security question warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>

				<input id="newSecurityAnser" type="text" name="securityAnswer" class="field" placeholder="Your answer" required pattern=".{1,60}" title="Answer must be equal or under 60 characters." value="">

				<!-- Security answer warnings -->
				<?php
					if($_SERVER["REQUEST_METHOD"] == "POST") {

					}
				?>
				<input type="submit" name="btnSubscribe" value="Create account">
			</form>
		</div>
	</div>

	<!-- Footer -->
	<?php include_once("$root/public/layout/footer.php"); ?>
</body>
<script>
	var form = document.getElementById("FormSubscribe"),
		fields = document.querySelectorAll(".field");

	fields.forEach(function(field) {
		if (!field.parentNode.classList.contains("flexput") || field.classList.contains("first")) {
			var warning = document.createElement("div"),
			icon = document.createElement("i"),
			message = document.createElement("span");

			message.textContent = field.getAttribute("title");

			icon.classList.add("fas", "fa-exclamation-triangle");

			warning.classList.add("warning");
			warning.style.display = "none";
			warning.appendChild(icon);
			warning.appendChild(message);

			if (field.classList.contains("first"))
				field.parentNode.parentNode.insertBefore(warning, field.parentNode.nextSibling);
			else
				field.parentNode.insertBefore(warning, field.nextSibling);
		}

		field.addEventListener("invalid", function(event) {
			event.preventDefault();
			if(!event.target.validity.valid) {
				if (field.parentNode.classList.contains("flexput"))
					field.parentNode.nextElementSibling.style.display = "block";
				else
					field.nextElementSibling.style.display = "block";
			}
		});

		field.addEventListener("focus", function(event) {
			if (field.parentNode.classList.contains("flexput")) {
				if(field.parentNode.nextElementSibling.style.display === "block")
					field.parentNode.nextElementSibling.style.display = "none";
			}
			else if (field.nextElementSibling.style.display === "block")
				field.nextElementSibling.style.display = "none";
		});
	});


</script>
</html>
