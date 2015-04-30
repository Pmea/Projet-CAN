
var nbEtats = document.getElementsByClassName("etat").length;
var i;
for(i=0; i<nbEtats; i++) {
    document.getElementById("raccourcis").innerHTML = 
        document.getElementById("raccourcis").innerHTML + 
        "<label for=\"selecteurEtat"+(i+1)+"\">"+(i+1)+"</label>";
}
