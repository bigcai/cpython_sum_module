要使用C语言编写一个CPython扩展模块（也就是通常所说的C扩展），你需要遵循一系列步骤来创建一个可以在Python中调用的动态链接库。下面是一个简单的示例，演示如何创建一个C扩展模块，该模块提供一个函数，该函数接受两个整数参数并返回它们的和。

### 步骤 1: 创建C源文件

首先，创建一个C源文件，比如叫`sum.c`:

```c
#include <Python.h>

static PyObject* sum_module_sum(PyObject* self, PyObject* args) {
    int a, b;
    if (!PyArg_ParseTuple(args, "ii", &a, &b)) {
        return NULL;
    }
    return Py_BuildValue("i", a + b);
}

static PyMethodDef SumMethods[] = {
    {"sum", sum_module_sum, METH_VARARGS, "Sum two integers"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef summodule = {
    PyModuleDef_HEAD_INIT,
    "summodule",   /* name of module */
    NULL,          /* module documentation, may be NULL */
    -1,            /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    SumMethods
};

PyMODINIT_FUNC PyInit_summodule(void) {
    return PyModule_Create(&summodule);
}
```

这段代码定义了一个名为`summodule`的模块，其中包含一个名为`sum`的函数，该函数接受两个整数参数并返回它们的和。

### 步骤 2: 编译C源文件

你需要使用Python提供的`distutils`或其他构建工具（如`setuptools`）来编译C源文件。首先，创建一个`setup.py`文件：

```python
from distutils.core import setup, Extension

module1 = Extension('summodule',
                    sources=['sum.c'])

setup(name='SumModule',
      version='1.0',
      description='This is a demo C extension module',
      ext_modules=[module1])
```

### 步骤 3: 构建和安装

在命令行中，切换到包含`setup.py`和`sum.c`的目录，并运行以下命令来构建和安装模块：

```bash
python setup.py build_ext --inplace
python setup.py install
```

### 步骤 4: 测试

安装完成后，你可以在Python脚本或交互式环境中测试这个模块：

```python
import summodule

result = summodule.sum(3, 5)
print(result)  # 输出: 8
```

这个例子展示了如何用C语言编写一个简单的Python扩展模块。实际开发中，你可能需要处理更复杂的类型转换、异常处理和资源管理。CPython的官方文档提供了更多关于编写扩展模块的详细信息。



发布你的C扩展模块到GitHub并允许用户通过pip远程安装，涉及几个步骤：将代码托管到GitHub、创建一个PyPI兼容的分发包、上传至PyPI（可选），以及通过GitHub仓库直接安装。以下是详细步骤：

### 步骤 1: 将代码托管到GitHub

1. **初始化Git仓库**：在你的项目目录下，如果还没有初始化Git，执行以下命令：
   
   ```bash
   git init
   ```

2. **添加文件**：将所有文件添加到Git仓库中。
   
   ```bash
   git add .
   ```

3. **提交更改**：提交你的更改并附上描述信息。
   
   ```bash
   git commit -m "Initial commit"
   ```

4. **创建GitHub仓库**：在GitHub网站上创建一个新的仓库，注意不要勾选"Initialize this repository with a README"。

5. **关联本地仓库与GitHub仓库**：在Git Bash中，将你的本地仓库与GitHub仓库关联起来。替换`<username>`和`<repository>`为你的GitHub用户名和仓库名。
   
   ```bash
   git remote add origin https://github.com/<username>/<repository>.git
   ```

6. **推送代码**：将你的代码推送到GitHub仓库。
   
   ```bash
   git push -u origin main
   ```

### 步骤 2: 创建PyPI兼容的分发包（可选）

如果你希望用户能通过pip直接从PyPI安装，你需要创建一个分发包（wheel或tarball）。这通常涉及到创建一个`setup.py`文件（如果你还没有的话），并使用`setuptools`或`flit`等工具。上面的示例中已经包含了`setup.py`文件，所以你可以跳过这步直接打包。

### 步骤 3: 上传到PyPI（可选）

如果选择通过PyPI分发，你需要注册一个PyPI账号，然后使用`twine`上传分发包。这包括运行`python setup.py sdist bdist_wheel`来生成分发文件，然后使用`twine upload dist/*`上传它们。详细步骤请参考PyPI官方文档。

### 步骤 4: 通过GitHub仓库直接安装

用户可以直接通过pip从你的GitHub仓库安装你的包，无需上传到PyPI。在用户的终端中，他们可以运行以下命令：

```bash
pip install git+https://github.com/<username>/<repository>.git
```

确保用户安装了Git并且Python环境已经配置好`pip`。

这样，你就成功地将C扩展模块发布到了GitHub，并允许用户远程安装它。如果还上传到了PyPI，用户也可以通过传统的`pip install your-package-name`命令安装。