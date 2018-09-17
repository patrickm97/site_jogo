let canvas = document.getElementById("canvas");
let ctx = canvas.getContext("2d");

<!-- colocar imagens no canvas -->
let canocima = new Image();
canocima.src = "canocima.png";
let canobaixo = new Image();
canobaixo.src = "canobaixo.png";
let background = new Image();
background.src = "background.png";
let solo = new Image();
solo.src = "solo.png";
let flappy = new Image();
flappy.src = "flappy.png";

<!-- variáveis movimentação dos objetos -->
let fx = 10;  <!-- posição x do flappy -->
let fy = 140;  <!-- posição y do flappy -->
let gravidade = 1.9;
let dife;
let vao = 80;
let keys = [];
let pontos = 0;

<!-- lista para posição padrão dos canos -->
let cano = [];

cano[0] = {
    x: canvas.width,
    y: 0
};

<!-- mover para cima com as teclas UP ou W -->
document.body.addEventListener("keydown" , function(e){
    keys[e.keyCode] = true;
});
document.body.addEventListener("keyup" , function(e){
    keys[e.keyCode] = false;
});

<!-- função inicia apenas quando clicar no botão -->
document.getElementById("button").onclick = function() {
    desenha(0);
    return false;
};

function desenha(){

    ctx.drawImage(background,0,0);
    ctx.drawImage(flappy,fx,fy);
    fy += gravidade; <!-- move ele com a gravidade constantemente -->
    ctx.fillStyle = "#000";
    ctx.font = "25px arial";

    if (keys[38] == true){
        fy -= 6;
    }
    if (keys[87] == true){
        fy -= 6;
    }

    <!-- usando for para mudar as posições dos canos em um loop -->
    for(let i = 0; i < cano.length; i++){

        dife = canocima.height + vao;
        ctx.drawImage(canocima, cano[i].x, cano[i].y);
        ctx.drawImage(canobaixo, cano[i].x, cano[i].y + dife);

        cano[i].x--;

        if(cano[i].x == 145){
            cano.push({ <!-- push faz as alturas ficarem aleatórias -->
                x: canvas.width,
                y: Math.floor(Math.random()* canocima.height) - canocima.height
            })
        }

        if (cano[i].x == 5) { <!-- adiciona um ponto toda vez que passar os canos -->
            pontos = pontos + 1;
        }
    }
    ctx.drawImage(solo,0,canvas.height - solo.height);
    ctx.fillText("Pontuação: " + pontos,10,450);

    requestAnimationFrame(desenha);
}

