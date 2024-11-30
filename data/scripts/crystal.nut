/**
 * This script is used for crystals temporarily.
 */

function add_crystal();
{
  play_sound("sounds/coins_cleared.ogg");
  Tux.add_coins(10);
  Text.set_font("normal");
  Text.set_text("You got a crystal!")
  Text.fade_in(0)
  Text.fade_out(1);
}
