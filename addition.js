Drupal.behaviors.modal = {
  attach: function (context, settings) {   
    Drupal.settings.CToolsModal = {
      modalTheme: 'customModalTheme',
      throbberTheme: 'customModalThrobber',
      animation: 'fadeIn',
      animationSpeed: 'fast',
      modalSize: {
        type: 'fixed',
        width: 'auto',
        height: 'auto',
        addWidth: 0,
        addHeight: 0,
      },
      modalOptions: {
        opacity: .55,
        background: '#000'
      }
    }; 
    jQuery('#modal-content form:first').once('class').each(function(){
      var classes = this.className.split(' ');
      for(var i=0;i<classes.length;i++){
        classes[i] = 'modal-'+classes[i];
      }
      jQuery('#modalContent')[0].className = classes.join(' ');
      jQuery(window).resize();
      jQuery('body, html').animate({scrollTop :0}, '500');
    });
    jQuery('#modal-content > .node').once('class').each(function(){
      jQuery(window).resize();
      jQuery('body, html').animate({scrollTop :0}, '500');
    });
  }, 
};
Drupal.theme.prototype.customModalTheme = function () {
  var html = '';
  html += '  <div id="ctools-modal">'
  html += '    <div class="ctools-modal-content">';
  html += '      <div class="modal-header">';
  html += '        <a class="close" href="#">x</a>';
  html += '        <span id="modal-title" class="modal-title">&nbsp;</span>';
  html += '      </div>';
  html += '      <div id="modal-content" class="modal-content">';
  html += '      </div>';
  html += '    </div>';
  html += '  </div>';
  return html;
}
Drupal.theme.prototype.customModalThrobber = function () {
  var html = '';

  return html;
};