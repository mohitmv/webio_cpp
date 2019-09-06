#include "elements.hpp"

#include <string>
#include <vector>
#include <map>
#include <assert.h>

using std::string;
using std::map;

namespace webio {

// print("\n".join("case FrontEndElement::" + i + ":\n  return \"" + i + "\";" for i in a))
std::string ElementTypeString(FrontEndElement::ElementType type) {
  switch (type) {
    case FrontEndElement::TEXT:
      return "TEXT";
    case FrontEndElement::BUTTON:
      return "BUTTON";
    case FrontEndElement::TEXT_INPUT:
      return "TEXT_INPUT";
    case FrontEndElement::TEXT_AREA:
      return "TEXT_AREA";
    case FrontEndElement::DROP_DOWN:
      return "DROP_DOWN";
    case FrontEndElement::TOGGLE:
      return "TOGGLE";
    case FrontEndElement::MENU:
      return "MENU";
    case FrontEndElement::ICON:
      return "ICON";
    case FrontEndElement::SIMPLE_DIV:
      return "SIMPLE_DIV";
    case FrontEndElement::HORIZONTAL_DIV:
      return "HORIZONTAL_DIV";
    case FrontEndElement::CHECK_BOX:
      return "CHECK_BOX";
    case FrontEndElement::IMAGE:
      return "IMAGE";
    case FrontEndElement::CHECK_BOX_LIST:
      return "CHECK_BOX_LIST";
    case FrontEndElement::HORIZONTAL_TABS:
      return "HORIZONTAL_TABS";
    case FrontEndElement::VERTICAL_TABS:
      return "VERTICAL_TABS";
    case FrontEndElement::TAB:
      return "TAB";
    case FrontEndElement::VERTICAL_DIV:
      return "VERTICAL_DIV";
    case FrontEndElement::INLINED_DIV:
      return "INLINED_DIV";
    case FrontEndElement::ICON_BUTTON:
      return "ICON_BUTTON";
    default: assert(false);
  }
  return "";
}

// ToDo(Mohit): [Important] write python code to generate code below.
Json FrontEndElement::Export() const {
  map<string, Json> json_fields;

  // fields_to_export = ["text_string", "icon", "label_string", "color_theme", "font_size", "margin", "height", "width", "padding", "border_width", "src"];
  // output = "";
  // for field in fields_to_export:
  //   output += "if (this->has_" + field + ") {\n"
  //   output += "  json_fields[\"" + field + "\"] = Json(icon_);\n"
  //   output += "}\n"

  if (this->has_icon) {
    json_fields["icon"] = Json(icon_);
  }

  if (this->has_text_string) {
    json_fields["text_string"] = Json(text_string_);
  }

  if (this->has_label_string) {
    json_fields["label_string"] = Json(label_string_);
  }

  if (this->has_color_theme) {
    json_fields["color_theme"] = Json(color_theme_);
  }

  if (this->has_font_size) {
    json_fields["font_size"] = Json(font_size_);
  }

  if (this->has_margin) {
    json_fields["margin"] = Json(margin_);
  }

  if (this->has_height) {
    json_fields["height"] = Json(height_);
  }

  if (this->has_width) {
    json_fields["width"] = Json(width_);
  }

  if (this->has_padding) {
    json_fields["padding"] = Json(padding_);
  }

  if (this->has_border_width) {
    json_fields["border_width"] = Json(border_width_);
  }

  if (this->has_value) {
    json_fields["value"] = Json(value_);
  }

  if (this->has_default_rows) {
    json_fields["default_rows"] = Json(default_rows_);
  }

  if (this->has_selected_tab) {
    json_fields["selected_tab"] = Json(selected_tab_);
  }

  if (this->has_disabled) {
    json_fields["disabled"] = Json(disabled_);
  }

  if (this->has_allow_multiple) {
    json_fields["allow_multiple"] = Json(allow_multiple_);
  }

  if (this->has_src) {
    json_fields["src"] = Json(src_);
  }

  if (this->has_options) {
    std::vector<Json> json_string_values;
    for (const std::string& option : options_) {
      json_string_values.push_back(Json(option));
    }
    json_fields["options"] = Json(std::move(json_string_values));
  }

  if (true) { // ToDo(Saharsh): replace by HasChildren()
    std::vector<Json> children1;  // ToDo(Saharsh): fix this shit
    for (auto &child: children) {
      children1.push_back(std::move(child.Export()));
    }
    json_fields["children"] = Json(std::move(children1));
  }

  if (this->has_menu_options) {
    std::vector<Json> options;
    for (int i = 0; i < menu_options_.size(); i++) {
      Json onclick_id = menu_options_onclick_ids[i] == -1 ? Json(nullptr): Json(menu_options_onclick_ids[i]);
      options.push_back(Json::array {menu_options_[i].first, onclick_id});
    }
    json_fields["options"] = Json(std::move(options));
  }

  if (this->has_src) {
    json_fields["src"] = Json(src_);
  }

  if (this->has_onclick) {
    json_fields["onclick_id"] = Json(onclick_id);
  }
  if (this->has_onchange) {
    json_fields["onchange_id"] = Json(onchange_id);
  }
  json_fields["element_type"] = ElementTypeString(this->element_type);
  json_fields["element_id"] = this->element_id;
  return json_fields;
}

FrontEndElement InlinedDiv() {
  return FrontEndElement(FrontEndElement::INLINED_DIV);
}

FrontEndElement VDiv() {
  auto output = FrontEndElement(FrontEndElement::VERTICAL_DIV);
  return output;
}

FrontEndElement HDiv() {
  auto output = FrontEndElement(FrontEndElement::HORIZONTAL_DIV);
  return output;
}

FrontEndElement Div() {
  auto output = FrontEndElement(FrontEndElement::SIMPLE_DIV);
  return output;
}

FrontEndElement VDiv(vector<FrontEndElement>&& input) {
  auto output = FrontEndElement(FrontEndElement::VERTICAL_DIV);
  output.children = input;
  return output;
}

FrontEndElement HDiv(vector<FrontEndElement>&& input) {
  auto output = FrontEndElement(FrontEndElement::HORIZONTAL_DIV);
  output.children = input;
  return output;
}

FrontEndElement Div(vector<FrontEndElement>&& input) {
  auto output = FrontEndElement(FrontEndElement::SIMPLE_DIV);
  output.children = input;
  return output;
}

FrontEndElement InlinedDiv(vector<FrontEndElement>&& input) {
  auto output = FrontEndElement(FrontEndElement::INLINED_DIV);
  output.children = input;
  return output;
}

FrontEndElement Icon(const std::string& icon) {
  return FrontEndElement(FrontEndElement::ICON)
          .Icon(icon)
          .FontSize("16px");
}

FrontEndElement IconButton(const std::string& icon) {
  return FrontEndElement(FrontEndElement::ICON_BUTTON)
            .Icon(icon)
            .Disabled(false);
}

FrontEndElement TextInput(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::TEXT_INPUT)
            .LabelString(label_string)
            .Disabled(false)
            .Value("");
}

FrontEndElement TextArea(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::TEXT_AREA)
            .LabelString(label_string)
            .Value("")
            .DefaultRows(5)
            .Disabled(false);
}

FrontEndElement DropDown(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::DROP_DOWN)
            .LabelString(label_string)
            .Disabled(false)
            .AllowMultiple(false)
            .Selected(0)
            .SelectedList({})
            .Options({});
}

FrontEndElement Toggle(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::TOGGLE)
            .LabelString(label_string)
            .Disabled(false)
            .On(false);
}

FrontEndElement CheckBox(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::CHECK_BOX)
            .LabelString(label_string)
            .On(false);
}

FrontEndElement CheckBoxList(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::CHECK_BOX_LIST)
            .LabelString(label_string)
            .Disabled(false)
            .AllowMultiple(false)
            .Options({})
            .Selected(0)
            .SelectedList({});
}

FrontEndElement Menu(const std::string& icon) {
  return FrontEndElement(FrontEndElement::MENU)
          .Icon(icon)
          .FontSize("16px")
          .MenuOptions({})
          .Disabled(true);
}

FrontEndElement VSpace(const std::string& size) {
  return VDiv().Height(size);
}

FrontEndElement Text(const std::string& text_string) {
  return FrontEndElement(FrontEndElement::TEXT).TextString(text_string);
}

FrontEndElement Text(const std::vector<FrontEndElement>& inputs) {
  auto output = FrontEndElement(FrontEndElement::TEXT);
  output.children = inputs;
  return output;
}

FrontEndElement HTabs() {
  return FrontEndElement(FrontEndElement::HORIZONTAL_TABS);
}

FrontEndElement VTabs() {
  return FrontEndElement(FrontEndElement::VERTICAL_TABS);
}

FrontEndElement Tab(const std::string& text_string) {
  return FrontEndElement(FrontEndElement::TAB).TextString(text_string);
}

FrontEndElement Button(const std::string& label_string) {
  return FrontEndElement(FrontEndElement::BUTTON)
            .LabelString(label_string)
            .Disabled(false)
            .ColorTheme("default");
}


FrontEndElement Image(const std::string& src) {
  return FrontEndElement(FrontEndElement::IMAGE).Src(src);
}

} // namespace webio
