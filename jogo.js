let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");

<!-- variáveis movimentação dos objetos -->
let fx = 10;  <!-- posição x inicial do Mario -->
let fy = 145;  <!-- posição y inicial do Mario -->
let raio = 23; <!-- raio para diminuir o tamanho da imagem original do Mario -->
let keys = [];
let cano = [];
let pontos = 0;

<!-- os primeiros canos aparecerão sempre na mesma posição -->
cano[0] = {
    x: canvas.width,
    y: 1.5
};

<!-- mover para cima apenas com as teclas UP e W -->
document.body.addEventListener("keydown" , function(e){
    keys[e.keyCode] = true;
});
document.body.addEventListener("keyup" , function(e){
    keys[e.keyCode] = false;
});

<!-- função inicia apenas quando o onclick for executado -->
document.getElementById("button").onclick = function() {
    desenha(0);
    return false;
};

<!-- colocar todas as imagens no canvas antes de chamar a função desenha-->
let canocima = new Image();
canocima.src = "canocima.png";
let canobaixo = new Image();
canobaixo.src = "canobaixo.png";
let backn = new Image();
backn.src = "backn.png";
let solon = new Image();
solon.src = "solon.png";
let mario = new Image();
mario.src = "mario.png";

function desenha(){

    ctx.drawImage(backn,0,0);
    ctx.drawImage(mario,fx,fy,raio*2,raio*2);
    <!-- assim que o Mario é desenhado, a sua posição y é puxada para baixo constantemente -->
    fy += 2.2;
    ctx.fillStyle = "black";
    ctx.font = "30px Courier New";
    <!-- Teclas UP e w fazem mover para cima -->
    if (keys[38] == true){
        fy -= 5.4;
    }
    if (keys[87] == true){
        fy -= 5.4;
    }
    <!-- usando for para mudar as posições da lista cano[i] em um loop constante -->
    for(let i = 0; i < cano.length; i++){

        ctx.drawImage(canocima, cano[i].x, cano[i].y);
        <!-- a diferença entre a posição y dos canos é igual a altura cano de cima + uma certa quantidade de pixels -->
        ctx.drawImage(canobaixo, cano[i].x, cano[i].y + canocima.height + 80);
        <!-- fazer os canos, que irão variar aleatóriamente após o primeiro, irem para a esquerda constantemente -->
        cano[i].x--;
        <!-- adiciona um ponto toda vez que passar os canos -->
        if (cano[i].x == 6) {
            pontos += 1;
        }
        <!-- detectar colisão com o solo e com os canos -->
        if (fy + 24 >=  canvas.height - 60 || fx + 24 <= cano[i].x + canocima.width && fx + 24 >= cano[i].x && (fy + 24 >= cano[i].y + canocima.height + 80 || fy + 9 <= cano[i].y + canocima.height)) {
            let x = document.getElementById("button2");
            <!-- aparecer a mensagem GAME OVER no botão transparente apenas com a colisão -->
            x.innerHTML = "GAME OVER";
            <!-- período de tempo para a página resetar após o GAME OVER -->
            function time(timeout) {
                setTimeout("location.reload(true);",timeout);}
            window.onload = time(250); <!-- 0.25 segundos -->
        }
        <!-- push traz novos canos a tela toda vez que o anterior chegar até um pouco antes da metade do canvas-->
        if(cano[i].x == 145){
            cano.push({
                x: canvas.width,
                <!-- math.random gera uma altura aleatória * a altura cano de cima e depois subtrai pela altura cano de cima -->
                y: Math.floor(Math.random()* canocima.height) - canocima.height
            })
        }
    }
    <!-- desenhar o solo e o texto apenas no final da função, para que eles se sobressaiam sobre os canos e o background -->
    ctx.drawImage(solon,0,canvas.height - 60);
    ctx.fillText("Pontuação: " + pontos,10,400);

    requestAnimationFrame(desenha);
}

