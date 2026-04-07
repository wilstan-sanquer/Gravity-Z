const socket = new WebSocket ("ws://localhost:8080");

socket.onopen = () => {
    console.log("Connecte au serveur");
    socket.send("Salut le backend");
};

socket.onmessage = (event) => {
    console.log("Reponse du serveur : ", event.data);
};

socket.onclose = () => {
    console.log("Connexion perdu");
};