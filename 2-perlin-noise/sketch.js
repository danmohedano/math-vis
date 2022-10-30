
let mode = 0;
let change_button;
let lod = 4; let falloff = 0.2; let color_diff = 50;
let lod_slider, falloff_slider, color_slider;

function setup() {
    createCanvas(800, 400);
    background (127);
    // Create Change Mode button
    change_button = createButton('Swap Color');
    change_button.position(0, 0);
    change_button.mousePressed(change_mode);
    // Create sliders to configure the noise parameters and colors
   lod_slider = createSlider(1, 5, lod);
   falloff_slider = createSlider(0, 1, falloff, 0.01);
   color_slider = createSlider(10, 1000, color_diff);

   lod_slider.position(150, 0);
   lod_slider.style('width', '90px');
   falloff_slider.position(250, 0);
   falloff_slider.style('width', '90px');
   color_slider.position(350, 0);
   color_slider.style('width', '90px');
}

function change_mode(){
    mode = (mode + 1) % 2;
}

function draw() {
    // Read slider values
    lod = lod_slider.value();
    falloff = falloff_slider.value();
    color_diff = color_slider.value();

    // Draw Perlin noise
    loadPixels();
    let c;
    for (let x = 0; x < width; x++){
        for (let y = 0; y < height; y++){
            // Calculate colors
            if (mode == 0){
                c = bw_perlin(x, y);
            } else {
                c = color_perlin(x, y);
            }
            set(x, y, c);
        }
    }
    updatePixels();
}

function bw_perlin(x, y){
    let c = map(noise((x - mouseX) * falloff, (y - mouseY) * falloff), 0, 1, 0, 255);
    return color(floor(c), floor(c), floor(c));
}

function color_perlin(x, y){
    let r, g, b;
    r = map(noise((x - mouseX) * falloff, (y - mouseY) * falloff), 0, 1, 0, 255);
    g = map(noise((x - mouseX + color_diff) * falloff, (y - mouseY + color_diff) * falloff), 0, 1, 0, 255);
    b = map(noise((x - mouseX + color_diff * 2) * falloff, (y - mouseY + color_diff * 2) * falloff), 0, 1, 0, 255);
    return color(floor(r), floor(g), floor(b));
}
