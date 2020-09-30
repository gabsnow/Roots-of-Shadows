function enableFieldEdit(e) {
  var element = e.currentTarget instanceof HTMLDivElement ? e.currentTarget : e.currentTarget.parentElement,
      newInput = createNewInput(element),
      submitBtn = createSubmitBtn(element),
      cancelBtn = createCancelBtn(element);

  restrictMultipleEdits();

  element.previousElementSibling.remove();

  if(element.classList.contains("pass"))
    element.previousElementSibling.remove();

  element.parentElement.insertBefore(newInput, element);
  element.parentElement.insertBefore(submitBtn, element);
  element.parentElement.insertBefore(cancelBtn, element);

  element.remove();
}

function restrictMultipleEdits() {
    otherCancelBtn = document.querySelector(".account.btn.cancel");

    if(otherCancelBtn) {
      if(typeof otherCancelBtn.click == "function")
        otherCancelBtn.click();
      else if(typeof otherCancelBtn.onclick == "function")
        otherCancelBtn.onclick();
    }
}

function createCancelBtn(element) {
  var cancelBtn = document.createElement("div"),
      cancelBtnIcon = document.createElement("i"),
      isPassword = element.classList.contains("pass"),
      value = isPassword ? element.previousElementSibling.value : element.previousElementSibling.innerText;

  cancelBtn.classList.add("account", "btn", "cancel");
  cancelBtnIcon.classList.add("fas", "fa-times-circle");

  cancelBtn.appendChild(cancelBtnIcon);

  cancelBtn.addEventListener("click", function(ev) {
    var cancelElement = ev.currentTarget instanceof HTMLDivElement ? ev.currentTarget : ev.currentTarget.parentElement,
        span = document.createElement("span"),
        div = document.createElement("div"),
        i = document.createElement("i"),
        isPassword = element.classList.contains("pass");

    span.classList.add("account-data");
    span.innerText = isPassword ? "********" : value;
    div.classList.add("account", "btn");

    div.addEventListener("click", enableFieldEdit);
    i.classList.add("fas", "fa-edit");

    div.appendChild(i);

    cancelElement.previousElementSibling.remove();
    cancelElement.previousElementSibling.remove();

    cancelElement.parentElement.insertBefore(span, cancelElement);

    if(isPassword) {
      div.classList.add("pass");
      var hiddenInput = document.createElement("input");
      hiddenInput.setAttribute("type", element.classList.contains("can-see") ? "text" : "password");
      hiddenInput.classList.add("hide");
      hiddenInput.value = value;
      cancelElement.parentElement.insertBefore(hiddenInput, cancelElement);
    }

    cancelElement.parentElement.insertBefore(div, cancelElement);

    cancelElement.remove();
  });

  return cancelBtn;
}

function createNewInput(element) {
  var newInput = document.createElement("input"),
      isPassword = element.classList.contains("pass"),
      value = isPassword ? element.previousElementSibling.value : element.previousElementSibling.innerText,
      placeholder = isPassword ? element.previousElementSibling.previousElementSibling.previousElementSibling.innerText : element.previousElementSibling.previousElementSibling.innerText;

  newInput.style.marginLeft = "30px";

  if(isPassword)
    newInput.setAttribute("type", element.classList.contains("can-see") ? "text" : "password");
  else
    newInput.setAttribute("type", "text");

  placeholder = placeholder.substring(0, placeholder.length - 2);
  newInput.setAttribute("placeholder", placeholder);
  newInput.value = isPassword ? "" : value;

  return newInput;
}

function createSubmitBtn(element) {
  var submitBtn = document.createElement("div"),
      submitBtnIcon = document.createElement("i"),
      isPassword = element.classList.contains("pass");

  submitBtn.classList.add("account", "btn", "submit");
  submitBtnIcon.classList.add("fas", "fa-check-circle");

  submitBtn.appendChild(submitBtnIcon);

  submitBtn.addEventListener("click", function(ev) {
    var subElement = ev.currentTarget instanceof HTMLDivElement ? ev.currentTarget : ev.currentTarget.parentElement,
        newValue = subElement.previousElementSibling.value,
        span = document.createElement("span"),
        div = document.createElement("div"),
        i = document.createElement("i");

    if(!isPassword)
      span.classList.add("account-data");

    span.innerText = isPassword ? "********" : newValue;
    div.classList.add("account", "btn");

    div.addEventListener("click", enableFieldEdit);
    i.classList.add("fas", "fa-edit");

    div.appendChild(i);

    if(isPassword) {
      div.classList.add("pass");
      var hiddenInput = document.createElement("input");
      hiddenInput.setAttribute("type", element.classList.contains("can-see") ? "text" : "password");
      hiddenInput.classList.add("hide", "account-data");
      hiddenInput.value = newValue;
    }

    subElement.nextElementSibling.remove();
    subElement.previousElementSibling.remove();

    subElement.parentElement.insertBefore(span, subElement);

    if(isPassword)
      subElement.parentElement.insertBefore(hiddenInput, subElement);

    subElement.parentElement.insertBefore(div, subElement);

    subElement.remove();

    if(window.XMLHttpRequest) {
      let xhr = new XMLHttpRequest();
      let formData = new FormData();
      var dataElements = document.querySelectorAll(".account-data");

      var arrayOfKeys = ["username", "email", "password", "securityQuestion", "securityAnswer"];

      for(var x = 0; x < dataElements.length; x++) {
        if(dataElements[x] instanceof HTMLInputElement)
          formData.append(arrayOfKeys[x], dataElements[x].value);
        else
          formData.append(arrayOfKeys[x], dataElements[x].innerText);
      }

      // for (var pair of formData.entries()) {
      //   console.log(pair[0]+ ', ' + pair[1]);
      // }

      formData.append("SubmitUpdateUser", "true");

      xhr.open("POST", "index.php?action=updateMember", true);
      xhr.onreadystatechange = function() {
        if(xhr.readyState === 4 && xhr.status === 200) {
          var resp = xhr.response;
          //alert(resp);
        }
        else {
          //alert("error");
        }
      }

      xhr.send(formData);
    }
  });

  return submitBtn;
}
