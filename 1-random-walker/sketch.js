

let walker;

function setup() {
  createCanvas(1920, 960);
  walker = new Walker();
  background (127);
}

function draw() {
  walker.step();
  walker.render();
}

class Walker{
    constructor(){
        this.x = width / 2;
        this.y = height / 2;
    }

    render(){
        stroke(0);
        strokeWeight(5);
        point(this.x, this.y);
    }

    step(){
        var choice = floor(random(4));
        var moves = [[5, 0], [-5, 0], [0, 5], [0, -5]];
        
        this.x += moves[choice][0];
        this.y += moves[choice][1];
        
        this.x = constrain(this.x, 0, width - 1);
        this.y = constrain(this.y, 0, height - 1);
    }
}