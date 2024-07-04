/*
 * Copyright 2022 netease. All rights reserved.
 * Author zhaochaochao@corp.netease.com
 * Date   2023/04/27
 * Brief  Tensorflow tensor converters. Converter grps msg to tf tensor when preprocess, and convert tf tensor to grps
 * msg when postprocess.
 */

#include "tf_tensor_converter.h"

#include <tensorflow/core/framework/tensor.h>
#include <tensorflow/core/framework/tensor_shape.h>

#include "logger/logger.h"

#define TF_TENSOR_CONVERTER_DEBUG 0

#if TF_TENSOR_CONVERTER_DEBUG
#include "google/protobuf/text_format.h"
#endif

#define LIST_TO_TF_TENSOR(list, tensor, tensor_dtype, offset) \
  do {                                                        \
    auto tensor_data = tensor.flat<tensor_dtype>();           \
    if (tensor_size == list.size()) {                         \
      for (int i = 0; i < tensor_size; ++i) {                 \
        tensor_data(i + offset) = tensor_dtype(list.at(i));   \
      }                                                       \
    } else {                                                  \
      err_list_size = list.size();                            \
      goto SIZE_ERROR;                                        \
    }                                                         \
  } while (0)

namespace netease::grps {
void TfTensorConverter::Init(const std::string& path, const YAML::Node& args) {
  Converter::Init(path, args);
  LOG4(INFO, "tensorflow tensor converter init, path: " << path << ", args: " << args);
}

tensorflow::DataType TfTensorConverter::GTensorType2TfType(::grps::protos::v1::DataType dtype) {
  switch (dtype) {
    case ::grps::protos::v1::DataType::DT_UINT8:
      return tensorflow::DT_UINT8;
    case ::grps::protos::v1::DataType::DT_INT8:
      return tensorflow::DT_INT8;
    case ::grps::protos::v1::DataType::DT_INT16:
      return tensorflow::DT_INT16;
    case ::grps::protos::v1::DataType::DT_INT32:
      return tensorflow::DT_INT32;
    case ::grps::protos::v1::DataType::DT_INT64:
      return tensorflow::DT_INT64;
    case ::grps::protos::v1::DataType::DT_FLOAT16:
      return tensorflow::DT_HALF;
    case ::grps::protos::v1::DataType::DT_FLOAT32:
      return tensorflow::DT_FLOAT;
    case ::grps::protos::v1::DataType::DT_FLOAT64:
      return tensorflow::DT_DOUBLE;
    case ::grps::protos::v1::DataType::DT_STRING:
      return tensorflow::DT_STRING;
    default:
      LOG4(ERROR, "tf tensor converter dtype error, unsupported dtype: " << dtype);
      throw ConverterException("tf tensor converter dtype error, unsupported dtype.");
  }
}

void TfTensorConverter::GTensor2TfTensor(const ::grps::protos::v1::GenericTensor& g_tensor,
                                         const std::string& tensor_name,
                                         tensorflow::Tensor& tensor,
                                         size_t tensor_size,
                                         size_t offset) {
  long long err_list_size = 0;
  switch (g_tensor.dtype()) {
    case ::grps::protos::v1::DataType::DT_UINT8: {
      LIST_TO_TF_TENSOR(g_tensor.flat_uint8(), tensor, tensorflow::uint8, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_INT8: {
      LIST_TO_TF_TENSOR(g_tensor.flat_int8(), tensor, tensorflow::int8, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_INT16: {
      LIST_TO_TF_TENSOR(g_tensor.flat_int16(), tensor, tensorflow::int16, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_INT32: {
      LIST_TO_TF_TENSOR(g_tensor.flat_int32(), tensor, tensorflow::int32, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_INT64: {
      LIST_TO_TF_TENSOR(g_tensor.flat_int64(), tensor, tensorflow::int64, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_FLOAT16: {
      LIST_TO_TF_TENSOR(g_tensor.flat_float16(), tensor, Eigen::half, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_FLOAT32: {
      LIST_TO_TF_TENSOR(g_tensor.flat_float32(), tensor, float, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_FLOAT64: {
      LIST_TO_TF_TENSOR(g_tensor.flat_float64(), tensor, double, offset);
      break;
    }
    case ::grps::protos::v1::DataType::DT_STRING: {
      LIST_TO_TF_TENSOR(g_tensor.flat_string(), tensor, tensorflow::tstring, offset);
      break;
    }
    default:
      std::string error_msg = "generic tensor to tf tensor error, tensor: ";
      error_msg += tensor_name;
      error_msg += " unsupported dtype: ";
      error_msg += std::to_string(g_tensor.dtype());
      LOG4(ERROR, error_msg);
      throw ConverterException(error_msg);
  }
  return;

SIZE_ERROR:
  std::string shape_str("[");
  for (const auto& dim : g_tensor.shape()) {
    shape_str += std::to_string(dim) + ",";
  }
  shape_str += "]";
  std::string error_msg = "generic tensor to tensorflow tensor error, tensor: ";
  error_msg += tensor_name;
  error_msg += " size not match, shape: ";
  error_msg += shape_str;
  error_msg += ", expected size: ";
  error_msg += std::to_string(tensor_size);
  error_msg += ", actual size: ";
  error_msg += std::to_string(err_list_size);
  LOG4(ERROR, error_msg);
  throw ConverterException(error_msg);
}

void TfTensorConverter::TfTensor2GTensor(const tensorflow::Tensor& tensor,
                                         const std::string& tensor_name,
                                         ::grps::protos::v1::GenericTensor& g_tensor,
                                         size_t tensor_size,
                                         size_t offset) {
  switch (tensor.dtype()) {
    case tensorflow::DataType::DT_UINT8: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_UINT8);
      g_tensor.mutable_flat_uint8()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<tensorflow::uint8>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_uint8(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_INT8: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_INT8);
      g_tensor.mutable_flat_int8()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<tensorflow::int8>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_int8(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_INT16: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_INT16);
      g_tensor.mutable_flat_int16()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<tensorflow::int16>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_int16(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_INT32: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_INT32);
      g_tensor.mutable_flat_int32()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<tensorflow::int32>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_int32(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_INT64: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_INT64);
      g_tensor.mutable_flat_int64()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<tensorflow::int64>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_int64(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_HALF: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_FLOAT16);
      g_tensor.mutable_flat_float16()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<Eigen::half>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_float16(i, float(flat(long(offset + i))));
      }
      break;
    }
    case tensorflow::DataType::DT_FLOAT: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_FLOAT32);
      g_tensor.mutable_flat_float32()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<float>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_float32(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_DOUBLE: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_FLOAT64);
      g_tensor.mutable_flat_float64()->Resize(int(tensor_size), 0);
      auto flat = tensor.flat<double>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.set_flat_float64(i, flat(long(offset + i)));
      }
      break;
    }
    case tensorflow::DataType::DT_STRING: {
      g_tensor.set_dtype(::grps::protos::v1::DataType::DT_STRING);
      g_tensor.mutable_flat_string()->Reserve(int(tensor_size));
      auto flat = tensor.flat<tensorflow::tstring>();
      for (int i = 0; i < int(tensor_size); ++i) {
        g_tensor.add_flat_string(flat(long(offset + i)));
      }
      break;
    }
    default:
      std::string error_msg = "tensorflow tensor to generic tensor error, tensor: ";
      error_msg += tensor_name;
      error_msg += " unsupported dtype: ";
      error_msg += std::to_string(tensor.dtype());
      LOG4(ERROR, error_msg);
      throw ConverterException(error_msg);
  }
}

void TfTensorConverter::PreProcess(const ::grps::protos::v1::GrpsMessage& input,
                                   std::vector<std::pair<std::string, TensorWrapper>>& output,
                                   GrpsContext& context) {
#if TF_TENSOR_CONVERTER_DEBUG
  std::string str;
  google::protobuf::TextFormat::PrintToString(input, &str);
  LOG4(INFO, "tensorflow tensor converter pre process, input: " << str);
#endif
  if (input.has_gtensors()) { // generic tensor pb.
    const auto& g_tensors = input.gtensors();

    // Check size.
    if (g_tensors.tensors_size() == 0) {
      LOG4(ERROR, "tf tensor converter pre process error, gtensors tensors size is 0.");
      throw ConverterException("tf tensor converter pre process error, gtensors tensors size is 0.");
    }

    // Check names.
    bool has_name = !g_tensors.tensors(0).name().empty();
    for (const auto& g_tensor : g_tensors.tensors()) {
      if ((has_name && g_tensor.name().empty()) || (!has_name && !g_tensor.name().empty())) {
        LOG4(ERROR,
             "tf tensor converter pre process error, gtensors tensors should all have name or all have no "
             "name(will use default name).");
        throw ConverterException(
          "tf tensor converter pre process error, gtensors tensors should all have name or all have no name(will "
          "use default name).");
      }
    }

    for (int i = 0; i < g_tensors.tensors_size(); ++i) {
      auto& g_tensor = g_tensors.tensors(i);
      long long tensor_size = 1;
      tensorflow::TensorShape shape;
      for (const auto& dim : g_tensor.shape()) {
        tensor_size *= dim;
        shape.AddDim(dim);
      }
      std::shared_ptr<tensorflow::Tensor> tensor =
        std::make_shared<tensorflow::Tensor>(GTensorType2TfType(g_tensor.dtype()), shape);
      GTensor2TfTensor(g_tensor, has_name ? g_tensor.name() : "", *tensor, tensor_size, 0);
      output.emplace_back(has_name ? g_tensor.name() : "", std::move(tensor));
    }
  } else {
    LOG4(ERROR, "tensorflow tensor converter pre process error, input has no gtensors.");
    throw ConverterException("tensorflow tensor converter pre process error, input has no gtensors.");
  }

#if TF_TENSOR_CONVERTER_DEBUG
  for (const auto& tensor : output) {
    LOG4(INFO, "tensorflow tensor converter pre process, tensor name: " << tensor.first << ", tensor: "
                                                                        << tensor.second.tf_tensor->DebugString());
  }
#endif
}

void TfTensorConverter::PostProcess(const std::vector<std::pair<std::string, TensorWrapper>>& input,
                                    ::grps::protos::v1::GrpsMessage& output,
                                    GrpsContext& context) {
#if TF_TENSOR_CONVERTER_DEBUG
  for (const auto& tensor : input) {
    LOG4(INFO, "tensorflow tensor converter post process, tensor name: " << tensor.first << ", tensor: "
                                                                         << tensor.second.tf_tensor->DebugString());
  }
#endif
  for (const auto& [name, tensor_wrapper] : input) {
    auto& tensor = *tensor_wrapper.tf_tensor;
    ::grps::protos::v1::GenericTensor g_tensor;

    // Set name.
    g_tensor.set_name(name);

    // Set shape.
    const auto& shape = tensor.shape();
    for (int i = 0; i < shape.dims(); ++i) {
      g_tensor.add_shape(shape.dim_size(i));
    }

    // Set data.
    TfTensor2GTensor(tensor, name, g_tensor, tensor.NumElements(), 0);
    *output.mutable_gtensors()->add_tensors() = std::move(g_tensor);
  }

#if TF_TENSOR_CONVERTER_DEBUG
  std::string str;
  google::protobuf::TextFormat::PrintToString(output, &str);
  LOG4(INFO, "tensorflow tensor converter post process, output: " << str);
#endif
}

void TfTensorConverter::BatchPreProcess(std::vector<const ::grps::protos::v1::GrpsMessage*>& inputs,
                                        std::vector<std::pair<std::string, TensorWrapper>>& output,
                                        std::vector<GrpsContext*>& ctxs) {
#if TF_TENSOR_CONVERTER_DEBUG
  for (const auto& input : inputs) {
    std::string str;
    google::protobuf::TextFormat::PrintToString(*input, &str);
    LOG4(INFO, "tf tensor converter batch pre process, input: " << str);
  }
#endif

  if (inputs.size() != ctxs.size()) {
    LOG4(ERROR, "tf tensor converter batch pre process error, inputs size not match ctxs size.");
    throw ConverterException("tf tensor converter batch pre process error, inputs size not match ctxs size.");
  }

  // 1. Initialize batched tensors names, dtype and shape from all inputs.
  std::vector<std::string> tensor_names;
  std::vector<tensorflow::DataType> tensor_dtypes;
  std::vector<tensorflow::TensorShape> tensor_shapes;
  size_t total_batch_size = 0;
  for (int i = 0; i < inputs.size(); i++) {
    const auto& g_tensors = inputs[i]->gtensors();
    // Check size.
    if (g_tensors.tensors_size() == 0) {
      LOG4(ERROR, "tf tensor converter batch pre process error, some one gtensors tensors size is 0.");
      throw ConverterException("tf tensor converter batch pre process error, some one gtensors tensors size is 0.");
    }

    // Check names and shape of each tensor.
    bool has_name = !g_tensors.tensors(0).name().empty();
    size_t cur_batch_size = g_tensors.tensors(0).shape(0);
    for (const auto& g_tensor : g_tensors.tensors()) {
      if ((has_name && g_tensor.name().empty()) || (!has_name && !g_tensor.name().empty())) {
        LOG4(ERROR,
             "tf tensor converter batch pre process error, gtensors tensors should all have name or all have no "
             "name(will use default name).");
        throw ConverterException(
          "tf tensor converter pre batch process error, gtensors tensors should all have name or all have no name(will "
          "use default name).");
      }
      if (g_tensor.shape_size() <= 1) {
        LOG4(ERROR, "tf tensor converter batch pre process error, tensor shape size should be greater than 1.");
        throw ConverterException(
          "tf tensor converter batch pre process error, tensor shape size should be greater than 1.");
      }
      if (cur_batch_size != g_tensor.shape(0)) {
        LOG4(ERROR, "tf tensor converter batch pre process error, batch size of each tensor not match.");
        throw ConverterException("tf tensor converter batch pre process error, batch size of each tensor not match.");
      }
    }

    if (i == 0) { // Initialize tensors names, dtypes and shapes use first input.
      for (int j = 0; j < g_tensors.tensors_size(); ++j) {
        tensor_names.emplace_back(has_name ? g_tensors.tensors(j).name() : "");
        tensor_dtypes.emplace_back(GTensorType2TfType(g_tensors.tensors(j).dtype()));
        tensorflow::TensorShape shape;
        for (int k = 0; k < g_tensors.tensors(j).shape_size(); ++k) {
          shape.AddDim(g_tensors.tensors(j).shape(k));
        }
        tensor_shapes.emplace_back(std::move(shape));
      }
    } else { // Compare names, dtypes and shapes of follow inputs with first input.
      if (g_tensors.tensors_size() != tensor_names.size()) {
        LOG4(ERROR, "tf tensor converter batch pre process error, tensors size not match.");
        throw ConverterException("tf tensor converter batch pre process error, tensors size not match.");
      }

      for (int j = 0; j < g_tensors.tensors_size(); ++j) {
        // Check names.
        if (tensor_names[j] != (has_name ? g_tensors.tensors(j).name() : "")) {
          LOG4(ERROR, "tf tensor converter batch pre process error, tensor names not match.");
          throw ConverterException("tf tensor converter batch pre process error, tensor names not match.");
        }
        // Check dtypes.
        if (tensor_dtypes[j] != GTensorType2TfType(g_tensors.tensors(j).dtype())) {
          LOG4(ERROR, "tf tensor converter batch pre process error, tensor dtypes not match.");
          throw ConverterException("tf tensor converter batch pre process error, tensor dtypes not match.");
        }
        // Check shapes[1:].
        if (tensor_shapes[j].dims() != g_tensors.tensors(j).shape_size()) {
          LOG4(ERROR, "tf tensor converter batch pre process error, tensor shapes not match.");
          throw ConverterException("tf tensor converter batch pre process error, tensor shapes not match.");
        }
        for (int k = 1; k < g_tensors.tensors(j).shape_size(); ++k) {
          if (tensor_shapes[j].dim_size(k) != g_tensors.tensors(j).shape(k)) {
            LOG4(ERROR, "tf tensor converter batch pre process error, tensor shapes not match.");
            throw ConverterException("tf tensor converter batch pre process error, tensor shapes not match.");
          }
        }
      }
    }
    total_batch_size += cur_batch_size;
  }
  for (size_t i = 0; i < tensor_names.size(); i++) {
    auto tensor_shape = tensor_shapes[i];
    tensor_shape.set_dim(0, int(total_batch_size));
    auto tensor = std::make_shared<tensorflow::Tensor>(tensor_dtypes[i], tensor_shape);
    output.emplace_back(tensor_names[i], std::move(tensor));
#if TF_TENSOR_CONVERTER_DEBUG
    LOG4(INFO, "tensorflow tensor converter batch pre process, tensor name: "
                 << tensor_names[i] << ", dtype: " << tensor_dtypes[i] << ", shape: " << tensor_shape.DebugString());
#endif
  }

  // 2. Insert data to batched tensors.
  std::vector<size_t> offsets(tensor_names.size(), 0);
  for (size_t i = 0; i < inputs.size(); i++) {
    const auto& g_tensors = inputs[i]->gtensors();
    for (int j = 0; j < g_tensors.tensors_size(); ++j) {
      size_t tensor_size = 1;
      for (const auto& dim : g_tensors.tensors(j).shape()) {
        tensor_size *= dim;
      }
      GTensor2TfTensor(g_tensors.tensors(j), tensor_names[j], *output[j].second.tf_tensor, tensor_size, offsets[j]);
      offsets[j] += tensor_size;
    }

    ctxs[i]->SetUserData<long long>(g_tensors.tensors(0).shape(0));
  }

#if TF_TENSOR_CONVERTER_DEBUG
  for (const auto& [name, tensor] : output) {
    LOG4(INFO, "tensorflow tensor converter batch pre process, tensor name: " << name << ", tensor: "
                                                                              << tensor.tf_tensor->DebugString());
  }
#endif
}

void TfTensorConverter::BatchPostProcess(const std::vector<std::pair<std::string, TensorWrapper>>& input,
                                         std::vector<::grps::protos::v1::GrpsMessage*>& outputs,
                                         std::vector<GrpsContext*>& ctxs) {
#if TF_TENSOR_CONVERTER_DEBUG
  for (const auto& [name, tensor] : input) {
    LOG4(INFO, "tensorflow tensor converter batch post process, tensor name: " << name << ", tensor: "
                                                                               << tensor.tf_tensor->DebugString());
  }
#endif

  if (outputs.size() != ctxs.size()) {
    LOG4(ERROR, "tf tensor converter batch post process error, outputs size not match ctxs size.");
    throw ConverterException("tf tensor converter batch post process error, outputs size not match ctxs size.");
  }

  std::vector<size_t> offsets(input.size(), 0);
  for (size_t i = 0; i < ctxs.size(); i++) {
    auto batch_size = ctxs[i]->GetUserData<long long>();
    for (size_t j = 0; j < input.size(); j++) {
      auto& [name, tensor_wrapper] = input[j];
      auto& tensor = *tensor_wrapper.tf_tensor;
      auto tensor_size = tensor.NumElements() / tensor.dim_size(0) * batch_size;

      ::grps::protos::v1::GenericTensor g_tensor;
      // Set name.
      g_tensor.set_name(name);
      // Set shape.
      g_tensor.add_shape(batch_size);
      for (int k = 1; k < tensor.dims(); ++k) {
        g_tensor.add_shape(tensor.dim_size(k));
      }
      // Set data.
      TfTensor2GTensor(tensor, name, g_tensor, tensor_size, offsets[j]);
      *outputs[i]->mutable_gtensors()->add_tensors() = std::move(g_tensor);

      offsets[j] += tensor_size;
    }
  }

#if TF_TENSOR_CONVERTER_DEBUG
  for (const auto& output : outputs) {
    std::string str;
    google::protobuf::TextFormat::PrintToString(*output, &str);
    LOG4(INFO, "tensorflow tensor converter batch post process, output: " << str);
  }
#endif
}
} // namespace netease::grps