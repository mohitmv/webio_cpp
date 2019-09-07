
#include "resources.hpp"

namespace webio {
namespace detail {
const string resources::html_page_content = "<!DOCTYPE html>\n<html>\n<head>\n  <title>web-input</title>\n  <link href='https://fonts.googleapis.com/css?family=Roboto' rel='stylesheet'>\n  <link href=\"https://fonts.googleapis.com/icon?family=Material+Icons\"\n      rel=\"stylesheet\">\n  <!-- {inlined_css_here:template_arg_0} -->\n</head>\n<body>\n<div id=\"loader\" ></div>\n<div id=\"main\" style=\"border: solid #ccc 0px;\" ></div>\n<div style=\"height: 40px;\" ></div>\n<div class=\"powered_by_section\" >Powered by <a href=\"https://github.com/mohitmv/webio\" target=\"_blank\" >WebIO</a></div>\n<script type=\"text/javascript\">\n  var webio = new (function() {\n    var thiso = this;\n\n    var is_null = function(a) {\n      return (a === undefined || a === null);\n    };\n\n    this.opened_menu = null;//replaced by dropdown-DOM of opened menu.\n    this.hide_all_dropdowns = function() {\n      if(thiso.opened_menu !== null) {\n        thiso.opened_menu.style.visibility = 'hidden';\n        thiso.opened_menu = null;\n        return true;\n      }\n      return false;\n    }\n    this.click_on_menu = function(obj, event) {\n      if(!thiso.hide_all_dropdowns()) {\n        var icon_position = obj.getBoundingClientRect();\n        var dropdown_obj = thiso.opened_menu = obj.nextElementSibling;\n        var root_obj = document.body.parentElement;\n        \n        var directional_margin = [\n          icon_position.top-dropdown_obj.clientHeight, \n          root_obj.clientWidth-(icon_position.left+dropdown_obj.clientWidth), \n          root_obj.clientHeight-(icon_position.top+icon_position.height+dropdown_obj.clientHeight), \n          icon_position.left + icon_position.width - dropdown_obj.clientWidth\n        ];//direction: up, right, down, left\n\n        var directions = [[1, 2], [1, 0], [3, 2], [3, 0]];//(horizonral, vertical)\n        var selected_direction = null;\n        var min_error = null;\n        var min_error_at;\n        for(var i=0; i<directions.length; i++) {\n          var c1 = directional_margin[directions[i][0]];\n          var c2 = directional_margin[directions[i][1]];\n          if(c1 >= 0 && c2 >= 0) {\n            selected_direction = i;\n            break;\n          } else {\n            var current_error = -1*(c1<0)*c1 + -1*(c2<0)*c2;\n            if(min_error === null || current_error < min_error) {\n              min_error = current_error;\n              min_error_at = i;\n            }\n          }\n        }\n        selected_direction = directions[(selected_direction === null ? min_error_at : selected_direction)];\n        var directional_postion = [\n          icon_position.top-dropdown_obj.clientHeight, \n          icon_position.left, \n          icon_position.top+icon_position.height, \n          icon_position.left + icon_position.width - dropdown_obj.clientWidth\n        ];// direction: up, right, down, left\n\n        var dropdown_left = directional_postion[selected_direction[0]]+ obj.offsetLeft - icon_position.left;\n        var dropdown_top = directional_postion[selected_direction[1]]+ obj.offsetTop - icon_position.top;\n\n        dropdown_obj.style.top = dropdown_top+\"px\";\n        dropdown_obj.style.left = dropdown_left+\"px\";\n        dropdown_obj.style.visibility = \"visible\";\n      }\n      event.stopPropagation();\n    };\n\n    var get_html = function(design_object) { //assert - design_object is valid.\n      var onclick_code = function(onclick_id) {\n        return (is_null(onclick_id) ? '': 'webio.action_api(\\''+onclick_id+'\\', event); ');\n      };\n      var onclick_code1 = function(onclick_id) {\n        return (is_null(onclick_id) ? '': ' onclick=\"webio.action_api(\\''+onclick_id+'\\', event)\" ');\n      };\n\n      var onchange_code = function(onchange_id) {\n        return (is_null(onchange_id) ? '': ' onchange=\"webio.action_api(\\''+onchange_id+'\\', event)\" ');\n      };\n      var style_code = function(design_object, attrs) {//assert ( attrs <= style_attr_mapping.keys() )\n        var style_attr_mapping = {\n          valign: \"vertical-align\",\n          bgcolor: \"background-color\",\n          border_width: \"border-width\",\n          border_color: \"border-color\",\n          font_size: \"font-size\",\n          line_height: \"line-height\"\n        };\n        var output = \"\";\n        for(var i in attrs) {\n          if(design_object[attrs[i]]) {\n            output += (style_attr_mapping[attrs[i]] || attrs[i])+':'+design_object[attrs[i]]+\";\";\n          }\n        }\n        return output;\n      };\n\n      var htmlEscape = function (str) {\n          return str.replace(/&/g, '&amp;')\n                    .replace(/\"/g, '&quot;')\n                    .replace(/'/g, '&#39;')\n                    .replace(/</g, '&lt;')\n                    .replace(/>/g, '&gt;')\n                    .replace(/\\n/g, '<br>')\n                    .replace(/  /g, '&nbsp;')\n                    .replace(/\\t/g, '&nbsp;');\n      };\n\n      var get_text_io_helper = function(design_object) {\n        var tag = (design_object.link || design_object.onclick_id) ? \"a\": \"span\";\n        var font_style_css = \"\";\n        if (design_object.font_style) {\n          var font_styles = {\n            \"i\": 'font-style: italic;', \n            'b': 'font-weight: 600;', \n            'u': 'text-decoration: underline;'\n          };\n          for(var i=0; i<design_object.font_style.length; i++) {\n            font_style_css += font_styles[design_object.font_style[i]];\n          }\n        }\n        var output = '<' + tag + ' ';\n        if (design_object.link) {\n          output += 'href=\"'+design_object.link+'\" ';\n        }\n        output += onclick_code1(design_object.onclick_id);\n        output += onchange_code(design_object.onchange_id);\n        output += ' style=\"' + style_code(design_object, [\"font_size\", \"color\", \"line_height\"])\n                             + font_style_css + '\"  >';\n        output += htmlEscape(design_object.text_string || \"\");\n        for(var i in design_object.children) {\n          output += get_text_io_helper(design_object.children[i]);\n        }\n        output += '</'+tag+'>';\n        return output;\n      }\n\n      var inputs_objects = thiso.inputs_objects = {};\n\n      var get_html_helper = function(design_object) {\n        if (design_object == null) {\n          alert(\"Server Error\");\n          return \"\";\n        } else if(design_object.element_type === \"HORIZONTAL_TABS\") {\n          var output = '<div class=\"horizontal_tab\" style=\"'+style_code(design_object, [\"bgcolor\", \"color\", \"padding\"])+'\" >';\n          for (var i = 0; i < design_object.children.length; i++) {\n            var classes = \" horizontal_tab_element \";\n            if (design_object.selected_tab === i) {\n              classes += \" selected \";\n            }\n            output += '<div class=\"' + classes + '\" ';\n            output += ' style=\"' + style_code(design_object.children[i], [\"bgcolor\", \"color\"]) + '\" ';\n            output += ' onclick=\"' + onclick_code(design_object.children[i].onclick_id) + ' webio.select_tab('+i+', event) \" >'\n            output += design_object.children[i].text_string +'</div>';\n          }\n          output += \"</div>\";\n          return output;\n        } else if(design_object.element_type === \"ICON_BUTTON\") {\n          return '<i '+onclick_code1(design_object.onclick_id)+' class=\"my-material-icon-button\" title=\"444\" >'+design_object.icon+'</i>';\n        } else if(design_object.element_type === \"BUTTON\") {\n          return '<button class=\"btn ' +(design_object.theme === \"black_in_white\" ? \"btn-default\": \"btn-primary\")+'\"  '+(design_object.disabled ? \"disabled\": \"\")+' '\n            + onclick_code1(design_object.onclick_id)+' >'+(design_object.label_string||\"\")+(is_null(design_object.icon) ? '': '<i class=\"my-material-icons\" >'+design_object.icon+'</i>')+ '</button>';\n        } else if (design_object.element_type === \"IMAGE\") {\n          return '<img src=\"'+design_object.src+'\" width=\"'+design_object.width+'\" height=\"'+design_object.height+'\" style=\"opacity: '+design_object.opacity+'; '+(design_object.rounded ? 'border-radius: 50%;': '')+' \" >';\n        } else if (design_object.element_type === \"TEXT\") {\n          return '<div class=\"text_div\"  >'+get_text_io_helper(design_object)+'</div>';\n        } else if (design_object.element_type === \"ICON\") {\n          return '<i class=\"my-material-icons\" style=\"font-size: '+design_object.font_size+'\" >'+design_object.icon+'</i>';\n        } else if (design_object.element_type === \"TEXT_INPUT\") {\n          inputs_objects[design_object.element_id] = design_object;\n          return '<div class=\"input-div\" ><label>'+design_object.label_string+'</label><br><input id=\"io_element_'+design_object.element_id+'\" type=\"text\" class=\"input-input\" placeholder=\"---\" ></div>';\n        } else if (design_object.element_type === \"TEXT_AREA\") {\n          inputs_objects[design_object.element_id] = design_object;\n          return '<div class=\"input-div\" ><label>'+design_object.label_string+'</label><br><textarea class=\"input-input\" id=\"io_element_'+design_object.element_id+'\" placeholder=\"---\" rows=\"'+design_object.default_rows+'\" ></textarea></div>';\n        } else if (design_object.element_type === \"DROP_DOWN\") {\n          inputs_objects[design_object.element_id] = design_object;\n          var output = '<div class=\"input-div-select\" ><label>'+design_object.label_string+'</label>'+(design_object.label_string === \"\" ? '':'<br>')+'<select class=\"input-input\" id=\"io_element_'+design_object.element_id+'\" '+(design_object.allow_multiple?'multiple':'')+' >';\n          for(var i=0; i<design_object.options.length; i++) {\n            var is_selected = design_object.allow_multiple ? (design_object.value.indexOf(i) != -1) : (i == design_object.value);\n            output += '<option value=\"'+(i)+'\" '+(is_selected ? 'selected':'')+' >'+design_object.options[i]+'</option>';\n          }\n          output += '</select></div>';\n          return output;\n        } else if(design_object.element_type === \"CHECK_BOX_LIST\") {\n          inputs_objects[design_object.element_id] = design_object;\n          var output = '<div class=\"input-div\" id=\"io_element_'+design_object.element_id+'\" >'+design_object.label_string;\n          for(var i = 0; i < design_object.options.length; i++) {\n            var is_selected = design_object.allow_multiple ? (design_object.value.indexOf(i) != -1) : (i == design_object.value);\n            output += '<br><label><input name=\"radio_'+design_object.element_id+'\" type=\"'+(design_object.allow_multiple ? 'checkbox':'radio')+'\" '+(is_selected ? 'checked': '')+' >'+design_object.options[i]+'</label>';\n          }\n          output += '</div>';\n          return output;\n        } else if(design_object.element_type === \"MENU\") {\n          var output = '<span><i class=\"my-material-icon-button\" onclick=\"webio.click_on_menu(this, event);\" >'+design_object.icon+'</i><div class=\"dropdown_content_wrapper\" ><div class=\"dropdown_content\" >';\n          for(var i = 0; i < design_object.options.length; i++) {\n            output += '<div class=\"dropdown_elements\" '+onclick_code1(design_object.options[i][1])+' >'+design_object.options[i][0]+'</div>';\n          }\n          output += '</div></div></span>';\n          return output;\n        } else if(design_object.element_type === \"INLINED_DIV\") {\n          var attrs = \" \";\n          attrs += onclick_code1(design_object.onclick_id);\n          var class_str = \"vertical_table \";\n          if (!is_null(design_object.onclick_id)) {\n            class_str += \"hover_cell\";\n          }\n          attrs += ' class=\"'+class_str+'\" ';\n          attrs += (design_object.align  ? 'align=\"'+design_object.align+'\"': '');\n          attrs += ' style=\"display: inline-block;' + style_code(design_object, [\"bgcolor\", \"width\", \"height\", \"border_width\", \"border_color\", \"margin\", \"color\", \"padding\"]) + '\" ';\n          var output = \"<div \" + attrs + \">\";\n          for (var i = 0; i < design_object.children.length; i++) {\n            output += get_html_helper(design_object.children[i]);\n          }\n          output += \"</div>\";\n          return output;\n        } else if(design_object.element_type === \"VERTICAL_DIV\") {\n          var attrs = \" \";\n          attrs += onclick_code1(design_object.onclick_id);\n          var class_str = \"vertical_table \";\n          if (!is_null(design_object.onclick_id)) {\n            class_str += \"hover_cell\";\n          }\n          attrs += ' class=\"'+class_str+'\" ';\n          attrs += (design_object.align  ? 'align=\"'+design_object.align+'\"': '');\n          attrs += ' style=\"' + style_code(design_object, [\"bgcolor\", \"width\", \"height\", \"border_width\", \"border_color\", \"margin\", \"color\", \"padding\"]) + '\" ';\n          var output = \"<div \" + attrs + \">\";\n          for (var i = 0; i < design_object.children.length; i++) {\n            output += \"<div>\" + get_html_helper(design_object.children[i]) + \"</div>\";\n          }\n          output += \"</div>\";\n          return output;\n        } else if(design_object.element_type === \"SIMPLE_DIV\") {\n          var attrs = \" \";\n          attrs += onclick_code1(design_object.onclick_id);\n          var class_str = \"vertical_table \";\n          if (!is_null(design_object.onclick_id)) {\n            class_str += \"hover_cell\";\n          }\n          attrs += ' class=\"'+class_str+'\" ';\n          attrs += (design_object.align  ? 'align=\"'+design_object.align+'\"': '');\n          attrs += ' style=\"' + style_code(design_object, [\"bgcolor\", \"width\", \"height\", \"border_width\", \"border_color\", \"margin\", \"color\", \"padding\"]) + '\" ';\n          var output = \"<div \" + attrs + \">\";\n          for (var i = 0; i < design_object.children.length; i++) {\n            output += get_html_helper(design_object.children[i]);\n          }\n          output += \"</div>\";\n          return output;\n        } else if (design_object.element_type === \"HORIZONTAL_DIV\") {\n          var attrs = \" \";\n          attrs += onclick_code1(design_object.onclick_id);\n          var class_str = \"table \";\n          if (!is_null(design_object.onclick_id)) {\n            class_str += \"hover_cell\";\n          }\n          attrs += ' class=\"'+class_str+'\" ';\n          attrs += (design_object.align  ? 'align=\"'+design_object.align+'\"': '');\n          attrs += ' style=\"' + style_code(design_object, [\"bgcolor\", \"width\", \"height\", \"border_color\", \"margin\", \"color\"]) + '\" ';\n          output = \"<div \" + attrs + \">\";\n          var cell_style = style_code(design_object, [\"valign\", \"padding\", \"border_width\"]);\n          for (var i = 0; i < design_object.children.length; i++) {\n            var child_width = design_object.children[i].width;\n            design_object.children[i].width = undefined;\n            output += '<div class=\"table_cell\" style=\"' + cell_style + 'width :'+(child_width || \"auto\") +';\" >'+get_html_helper(design_object.children[i])+'</div>';\n          }\n          output += '</div>';\n          return output;\n        } else {\n          console.log(\"Handle the \" + design_object.element_type + \" element\");\n          return null;\n        }\n      };\n      return get_html_helper(design_object);\n    };\n\n    var api_url = \"/v1/action\";\n    var api_call = function(url, data, callback) {\n      var xhttp = new XMLHttpRequest();\n      xhttp.onreadystatechange = function() {\n        if (this.readyState == 4 && this.status == 200) {\n          callback(this.response);\n        }\n      };\n      xhttp.open(\"POST\", url, true);\n      xhttp.setRequestHeader(\"Content-type\", \"application/json\");\n      xhttp.send(JSON.stringify(data));\n    }\n\n    var render_frame = this.render_frame = function(frame) {\n      document.getElementById(\"main\").innerHTML = get_html(frame);\n      thiso.set_default_values();\n    }\n\n\n    this.set_default_values = function() {\n      for(var i in thiso.inputs_objects) {\n        var io = thiso.inputs_objects[i];\n        if (io.element_type === 'TEXT_INPUT' || io.element_type === 'TEXT_AREA') {\n          document.getElementById(\"io_element_\"+io.element_id).value = io.value;\n        }\n      }\n    }\n\n    this.get_input_values = function() {\n      var output = {};\n      for(var i in thiso.inputs_objects) {\n        var io = thiso.inputs_objects[i];\n        var dom_elm = document.getElementById(\"io_element_\"+io.element_id);\n        if (io.element_type === 'TEXT_INPUT' ||\n            io.element_type === 'TEXT_AREA' ||\n            (io.element_type === 'DROP_DOWN' && !io.allow_multiple)) {\n          output[io.element_id] = dom_elm.value;\n          if(io.element_type == \"DROP_DOWN\") {\n            output[io.element_id] = parseInt(output[io.element_id]);\n          }\n        } else if(io.element_type === \"DROP_DOWN\" && io.allow_multiple) {\n          var selected = [];\n          for(var i=0; i<dom_elm.options.length; i++) {\n            dom_elm.options[i].selected ? selected.push(i):null;\n          }\n          output[io.element_id] = selected;\n        } else if(io.element_type === \"CHECK_BOX\") {\n          var radio_buttons = document.getElementsByName(\"radio_\"+io.element_id);\n          var selected = [];\n          for(var i=0; i<radio_buttons.length; i++) {\n            radio_buttons[i].checked ? selected.push(i):null;\n          }\n          output[io.id] = io.allow_multiple ? selected: selected[0];\n        } else {\n          alert(\"ToDo(*): Complete this implementation !\");\n        }\n      }\n      return output;\n    };\n\n    this.select_tab = function(tab_index, event) {\n      // event.target.classList.add(\"selected\");\n      // console.log(tab_index, event);\n    }\n\n    this.is_loading = false;\n\n    this.action_api = function(action_id, event) {\n      console.log(\"Triggered action: \" + action_id);\n      if (this.is_loading) {\n        console.log(\"Abandoned action. Another action was going on.\");\n        return;\n      }\n      document.getElementById(\"loader\").style.display = \"block\";\n      this.is_loading = true;\n      thiso.hide_all_dropdowns();\n      api_call(api_url, {action_id: parseInt(action_id),\n                         inputs: thiso.get_input_values(),\n                         client_instance_id: initial_frame_info.client_instance_id,\n                         server_instance_id: initial_frame_info.server_instance_id\n                        }, function(d) {\n        thiso.is_loading = false;\n        document.getElementById(\"loader\").style.display = \"none\";\n        var json_response = JSON.parse(d);\n        if(json_response.error.error_code == \"SUCCESS\") {\n          render_frame(json_response.frame);\n        } else {\n          alert(json_response.error.error_code + \" - Please reload !\");\n        }\n      });\n      event.stopPropagation();\n    }\n\n    this.window_onclick = function() {\n      thiso.hide_all_dropdowns();\n    }\n  })();\n  var tmp_frame_6703 = [null, {\n    frame: {\n      \"element_type\": \"BUTTON\",\n      \"element_id\": \"6\",\n      \"label_string\": \"Sample Button\",\n      \"theme\": \"default\",\n      \"icon\": null,\n      \"onclick_id\": undefined,\n    }\n  }];\n  // tmp_frame_6703[0] = {\"children\": [{\"children\": [{\"children\": [{\"children\": [], \"element_type\": \"TEXT\", \"text_string\": \"Mohit\"}, {\"children\": [], \"element_type\": \"TEXT\", \"text_string\": \"  \"}, {\"children\": [], \"element_type\": \"TEXT\", \"text_string\": \"Saini\", \"onclick_id\": 1}], \"element_type\": \"TEXT\", \"onclick_id\": 2}], \"element_type\": \"VLIST\", \"onclick_id\": 3}, {\"children\": [{\"children\": [{\"children\": [], \"element_type\": \"TEXT\", \"text_string\": \"Mohit\"}, {\"children\": [], \"element_type\": \"TEXT\", \"text_string\": \"  \"}, {\"children\": [], \"element_type\": \"TEXT\", \"text_string\": \"Saini\", \"onclick_id\": 4}], \"element_type\": \"TEXT\", \"onclick_id\": 5}], \"element_type\": \"VLIST\", \"onclick_id\": 6}], \"element_type\": \"HLIST\"};\n  var initial_frame_info = tmp_frame_6703[1];\n  webio.render_frame(initial_frame_info.frame);\n  window.onclick = function(event) {\n    webio.window_onclick();\n  }\n</script>\n</body>\n</html>\n";

const string resources::css_page_content = "\n\nhtml, body {\n\tmargin: 0px;\n\tpadding: 0px;\n  font-family: 'Roboto';\n}\n\n.btn {\n\tdisplay: inline-block;\n\tpadding: 6px 12px;\n\tmargin-bottom: 0;\n\tfont-size: 14px;\n\tfont-weight: 400;\n\tline-height: 1.42857143;\n\ttext-align: center;\n\twhite-space: nowrap;\n\tvertical-align: middle;\n\t-ms-touch-action: manipulation;\n\ttouch-action: manipulation;\n\tcursor: pointer;\n\t-webkit-user-select: none;\n\t-moz-user-select: none;\n\t-ms-user-select: none;\n\tuser-select: none;\n\tbackground-image: none;\n\tborder: 1px solid transparent;\n\tborder-radius: 4px;\n\tmargin: 10px;\n}\n\n\n\n.btn-primary {\n\tcolor: #fff;\n\tbackground-color: #337ab7;\n\tborder-color: #2e6da4;\n}\n\n.btn-primary:focus, .btn-primary:active, .btn-primary:hover {\n  color: #fff;\n  background-color: #286090;\n  border-color: #122b40;\n}\n\n\n\n\n.btn-default {\n\tcolor: #333;\n\tbackground-color: #fff;\n\tborder-color: #ccc;\n}\n\n.btn-default:hover, .btn-default:active, .btn-default:focus {\n  color: #333;\n  background-color: #e6e6e6;\n  border-color: #adadad;\n}\n\n.btn:disabled {\n  opacity: .65;\n  cursor: initial;\n}\n\n.btn-default:disabled {\n  color: #333;\n  background-color: #fff;\n  border-color: #ccc;\n}\n\n.btn-primary:disabled {\n  color: #fff;\n  background-color: #337ab7;\n  border-color: #2e6da4;\n}\n\n\n.my-material-icons, .my-material-icon-button {\n  font-family: 'Material Icons';\n  font-weight: normal;\n  font-style: normal;\n  letter-spacing: normal;\n  text-transform: none;\n  display: inline-block;\n  white-space: nowrap;\n  word-wrap: normal;\n  direction: ltr;\n  -webkit-font-feature-settings: 'liga';\n  -webkit-font-smoothing: antialiased;\n  color: inherit;\n}\n\n\n.my-material-icon-button {\n\tpadding: 5px;\n\tcursor: pointer;\n\tfont-size: 16px;\n\tborder-radius: 14px;\n\tcolor: #333;\n}\n\n.my-material-icon-button:hover {\n\tbackground-color: #ccc; \n\tpadding: 5px;\n}\n\n\n\n.input-div {\n\tmargin-left: 10px;\n\tmargin-right: 25px;\n\t/*margin-top: 10px;*/\n\tmargin-bottom: 25px;\n}\n\n.input-input {\n\twidth: 100%;\n\tmargin-bottom: 0;\n\tmargin-top: 2px;\n\tdisplay: block;\n\tfont-size: 14px;\n\tpadding: 6px 10px;\n\tcolor: #555;\n\tbackground-color: #fff;\n\tbackground-image: none;\n\tborder: 1px solid #ccc;\n\tborder-radius: 4px;\n\t-webkit-box-shadow: inset 0 1px 1px rgba(0,0,0,.075);\n\tbox-shadow: inset 0 1px 1px rgba(0,0,0,.075);\n\t-webkit-transition: border-color ease-in-out .15s,-webkit-box-shadow ease-in-out .15s;\n\t-o-transition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;\n\ttransition: border-color ease-in-out .15s,box-shadow ease-in-out .15s;\n}\n\ntextarea.input-input {\n\tresize: none;\n}\n\n.input-div-select {\n\tmargin: 20px 5px;\n\tmargin-top: 0px;\n\tmargin-bottom: 0px;\n\t/*margin-bottom: 25px;*/\n}\n\n\n\n.input-input:focus {\n  border-color: #66afe9;\n  outline: 0;\n  -webkit-box-shadow: inset 0 1px 1px rgba(0,0,0,.075), 0 0 8px rgba(102, 175, 233, .6);\n\t\t  box-shadow: inset 0 1px 1px rgba(0,0,0,.075), 0 0 8px rgba(102, 175, 233, .6);\n}\n.input-input::-moz-placeholder {\n  color: #999;\n  opacity: 1;\n}\n.input-input:-ms-input-placeholder {\n  color: #999;\n}\n.input-input::-webkit-input-placeholder {\n  color: #999;\n}\n\n\n.dropdown_elements {\n\tcolor: black;\n\tpadding: 12px 16px;\n\ttext-decoration: none;\n\tdisplay: block;\n\tcursor: pointer;\n}\n\n.dropdown_elements:hover {\n\tbackground-color: #ddd\n}\n\n\n.dropdown_content {\n\tbackground-color: #f1f1f1;\n\tmax-width: 300px;\n\toverflow: auto;\n\tbox-shadow: 0px 8px 16px 0px rgba(0,0,0,0.2);\n\tz-index: 1;\n\tdisplay: inline-block;\n}\n\n.dropdown_content_wrapper {\n\ttop: 0px;\n\tleft: 0px;\n\tdisplay: block; \n\tposition: absolute; \n\tvisibility: hidden;\n}\n\ndiv.table {\n\tdisplay: table;\n\twidth: 100%;\n\ttable-layout: fixed;\n\tborder-collapse: collapse;\n\tbox-sizing: border-box;\n  border: solid #ccc 0px;\n}\n\ndiv.table > div.table_cell {\n\tdisplay: table-cell;\n\tborder: solid #ccc 0px;\n\tborder-collapse: collapse;\n}\n\n\ndiv.vertical_table {\n\tborder-collapse: collapse;\n\tbox-sizing: border-box;\n\twidth: 100%;\n  border: solid #ccc 0px;\n  border-collapse: collapse;\n}\n\ndiv.hover_cell:hover {\n\tbackground-color: #eee;\n\tcursor: pointer;\n}\n\n\n\ndiv.text_div {\n\t/*width: 100%;*/\n\tmargin: 10px;\n}\n\na {\n\tcursor: pointer;\n\tcolor: rgb(0, 0, 230);\n}\n\n\na:hover {\n\ttext-decoration: underline;\n}\n\n\ndiv.horizontal_tab {\n  -webkit-box-shadow: inset 0 1px 3px 0 rgba(0,0,0,.2), 0 1px 1px 0 rgba(0,0,0,.14);\n  box-shadow: inset 0 1px 3px 0 rgba(0,0,0,.2), 0 1px 1px 0 rgba(0,0,0,.14);\n}\n\ndiv.horizontal_tab_element {\n  display: inline-block;\n  height: 40px;\n  line-height: 40px;\n  padding: 0px 10px;\n  cursor: pointer;\n  vertical-align: middle;\n}\n\ndiv.horizontal_tab_element:hover, div.horizontal_tab_element.selected {\n  background-color: #ccc;\n}\n\ndiv.card_div {\n  padding: 10px;\n  -webkit-box-shadow: inset 0 1px 1px rgba(0,0,0,.075);\n  box-shadow: inset 0 1px 1px rgba(0,0,0,.075);\n  margin-bottom: 10px;\n  box-sizing: border-box;\n}\n\n\n#loader {\n  position: fixed;\n  left: 0px;\n  top: 0px;\n  width: 100%;\n  height: 100%;\n  display: none;\n  background-repeat: no-repeat;\n  background-color: white;\n  z-index: 10000;\n  background-image: url(https://steamuserimages-a.akamaihd.net/ugc/267223080226461303/985912CAD9866AE8997702BB87823D78E1E66110/)\n}\n\n\n.powered_by_section {\n  position: fixed;\n  bottom: 0px;\n  right: 0px;\n  height: 30px;\n  margin-bottom: 0px;\n  padding-right: 40px;\n  background-color: white;\n}\n\n";
}
}

  